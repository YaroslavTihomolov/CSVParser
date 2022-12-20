//
// Created by я on 15.12.2022.
//

#ifndef CSVPARSER_CSVPARSER_H
#define CSVPARSER_CSVPARSER_H

#include <fstream>
#include "TuplePrint.h"
#include <sstream>
#include <utility>
#include "Exceptions.h"

template<class... Args>
class CSVParser {
private:
    std::ifstream file;

    std::string line;

    char lines_separator{};
    char column_separator{};
    char shielding{};

    int line_num{};

    template<class... Tuple>
    auto getTuple(int cur_pos, int_<sizeof...(Args)>) {
        if (cur_pos != 0 && cur_pos != (line.length() + 1)) throw Exceptions(line_num, cur_pos, WRONG_DATA, "WRONG_DATA");
        return std::make_tuple();
    }

    template<class T>
    T DataToHead(const std::string& substring, T data, int cur_pos) {
        std::stringstream tmp_s(substring);
        tmp_s >> data;
        if (!tmp_s.eof()) throw Exceptions(line_num,cur_pos + tmp_s.tellg() + 1, WRONG_DATA, "WRONG_DATA");
        return data;
    }

    char DataToHead(std::string substring, char data, int cur_pos) {
        if (substring.length() == 1) data = substring[0];
        else throw Exceptions(line_num, cur_pos, WRONG_DATA, "WRONG_DATA");
        return data;
    }

    unsigned char DataToHead(std::string substring, unsigned char data, int cur_pos) {
        if (substring.length() == 1) data = substring[0];
        else throw Exceptions(line_num, cur_pos, WRONG_DATA, "WRONG_DATA");
        return data;
    }

    std::string DataToHead(std::string substring, std::string data, int cur_pos) {
        data = substring;
        return data;
    }

    int GetRpos(int &cur_pos) {
        int r_pos;
        if (line[cur_pos] == shielding) {
            r_pos = line.find(shielding, ++cur_pos);
            if (r_pos == std::string::npos) return line.find(column_separator, --cur_pos);
        } else {
            r_pos = line.find(column_separator, cur_pos);
        }
        return r_pos;
    }

    template<class Head, class... Tuple, std::size_t pos>
    auto getTuple(int cur_pos, int_<pos>) {
        Head cur;
        int r_pos = GetRpos(cur_pos);
        std::string substring = line.substr(cur_pos, r_pos - cur_pos);
        if (substring.empty()) throw Exceptions(line_num, cur_pos + 1, WRONG_DATA, "WRONG_DATA");
        cur = DataToHead(substring, cur, cur_pos);
        r_pos += (line[r_pos] == shielding) ? 2 : 1;
        return std::tuple_cat(std::make_tuple(cur), getTuple<Tuple...>(r_pos, int_<pos + 1>()));
    }

    std::tuple<Args...> cur_tuple;

    void SkipLines(int lines) {
        while (lines--) {
            std::string line_to_skip;
            if (file.eof()) throw Exceptions(WRONG_COUNT_OF_LINES, "WRONG_COUNT_OF_LINES");
            std::getline(file, line_to_skip, lines_separator);
        }
    }

public:

    CSVParser() = default;

    CSVParser(std::ifstream &file_inp, int line_skip, char column, char sep_line, char shielding_inp) :
            lines_separator(sep_line), column_separator(column), shielding(shielding_inp), line_num(line_skip + 1) {
        file.basic_ios<char>::rdbuf(file_inp.rdbuf());
        SkipLines(line_skip);
        std::getline(file, line, lines_separator);
        cur_tuple = getTuple<Args...>(0, int_<0>());
    }

    template<class Iter>
    class CSVParserIterator {
        friend class CSVParser;

    private:
        typedef Iter iterator_type;

        typedef iterator_type &reference;

        iterator_type *value;
    public:

        CSVParserIterator(Iter *p) : value(p) {}

        CSVParserIterator(const CSVParserIterator &it) : value(it.value) {}

        bool operator!=(CSVParserIterator const &other) const {
            return value != other.value;
        }

        bool operator==(CSVParserIterator const &other) const {
            return value == other.value;
        }

        typename CSVParserIterator::reference operator*() const {
            return *value;
        }

        CSVParserIterator &operator++() {
            if (value->file.eof()) {
                *this = nullptr;
                return *this;
            }
            value->line_num++;
            std::getline(value->file, value->line, value->lines_separator);
            if (value->line.length() == 0)  {
                *this = nullptr;
                return *this;
            }
            value->cur_tuple = value->template getTuple<Args...>(0, int_<0>());
            return *this;
        }

    };

private:
    typedef CSVParserIterator<CSVParser> iterator;
    typedef CSVParserIterator<const CSVParser> const_iterator;

public:

    iterator begin() {
        CSVParser<Args...> *csvparser = this;
        return iterator(csvparser);
    }

    iterator end() {
        return nullptr;
    }

    const_iterator begin() const {
        CSVParser<Args...> *csvparser = this;
        return const_iterator(csvparser);
    }

    const_iterator end() const {
        return nullptr;
    }

    CSVParser(const CSVParser &) = delete;

    friend std::ostream &operator<<(std::ostream &out, const CSVParser &csvparser) {
        return out << csvparser.cur_tuple << '\n';
    }

};


/*auto getTuple(int cur_pos, int_<sizeof...(Args)>) {
    return std::make_tuple();
}

template <std::size_t pos>
auto getTuple(int cur_pos, int_<pos>) {
    int r_pos = line.find(',', cur_pos);
    std::string substring = line.substr(cur_pos, r_pos - cur_pos);
    std::tuple_element_t<pos, std::tuple<Args...>> tmp;
    std::istringstream(substring) >> tmp;
    return std::tuple_cat(std::make_tuple(tmp), getTuple(r_pos + 1, int_<pos + 1>()));
}*/


#endif //CSVPARSER_CSVPARSER_H

