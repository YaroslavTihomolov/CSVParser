//
// Created by я on 15.12.2022.
//

#ifndef CSVPARSER_CSVPARSER_H
#define CSVPARSER_CSVPARSER_H

#include <fstream>
#include "TuplePrint.h"
#include <sstream>

template<class... Args>
class CSVParser {
private:
    std::ifstream file;

    std::string line;

    auto getTuple(int cur_pos, int_<sizeof...(Args)>) {
        return std::make_tuple();
    }

    template <std::size_t pos>
    auto getTuple(int cur_pos, int_<pos>) {
        int r_pos = line.find(',', cur_pos);
        std::string substring = line.substr(cur_pos, r_pos - cur_pos);
        std::tuple_element_t<pos, std::tuple<Args...>> tmp;
        std::istringstream(substring) >> tmp;
        return std::tuple_cat(std::make_tuple(tmp), getTuple(r_pos + 1, int_<pos + 1>()));
    }

    std::tuple<Args...> cur_tuple;

    void SkipLines(int lines) {
        while (lines--) {
            std::string line_to_skip;
            std::getline(file, line_to_skip);
        }
    }

public:

    CSVParser() = default;

    CSVParser(std::ifstream& file_inp, int line_skip) {
        file.basic_ios<char>::rdbuf(file_inp.rdbuf());
        SkipLines(line_skip);
        std::getline(file, line);
        cur_tuple = getTuple(0, int_<0>());
    }

    template<class Iter>
    class CSVParserIterator {
        friend class CSVParser;

    private:
        typedef Iter iterator_type;

        typedef iterator_type& reference;

        iterator_type* value;
    public:

        CSVParserIterator(Iter* p): value(p) { }

        CSVParserIterator(const CSVParserIterator& it) : value(it.value) { }

        bool operator!=(CSVParserIterator const& other) const {
            return value != other.value;
        }

        bool operator==(CSVParserIterator const& other) const {
            return value == other.value;
        }

        typename CSVParserIterator::reference operator*() const {
            return *value;
        }

        CSVParserIterator& operator++() {
            if (value->file.eof())  {
                *this = nullptr;
                return *this;
            }
            std::getline(value->file, value->line);
            value->cur_tuple = value->getTuple(0, int_<0>());
            return *this;
        }

    };

private:
    typedef CSVParserIterator<CSVParser> iterator;
    typedef CSVParserIterator<const CSVParser> const_iterator;

public:

    iterator begin() {
        CSVParser<Args...>* csvparser = this;
        return iterator(csvparser);
    }

    iterator end() {
        return nullptr;
    }

    const_iterator begin() const {
        CSVParser<Args...>* csvparser = this;
        return const_iterator(csvparser);
    }

    const_iterator end() const {
        return nullptr;
    }

    CSVParser(const CSVParser&) = delete;

    friend std::ostream& operator<<(std::ostream& out, const CSVParser& csvparser) {
        return out << csvparser.cur_tuple << '\n';
    }

};

#endif //CSVPARSER_CSVPARSER_H

