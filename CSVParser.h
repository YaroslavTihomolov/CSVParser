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
    void SkipLines(std::ifstream& file, int lines) {
        while (lines--) {
            std::string line_to_skip;
            std::getline(file, line_to_skip);
        }
    }

    template<class Iter>
    class CSVParserIterator {
        friend class CSVParser<>;
    public:
        typedef Iter iterator_type;
        typedef std::input_iterator_tag iterator_category;
        typedef iterator_type value_type;
        typedef ptrdiff_t difference_type;
        typedef iterator_type& reference;
        typedef iterator_type* pointer;

        iterator_type* value;
    private:
        CSVParserIterator(Iter* p): value(p) { }


    public:
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


    };

    std::string line;

    auto getTuple(std::tuple<Args...> *types, int cur_pos, int_<sizeof...(Args)>) {
        return std::make_tuple();
    }

    template <std::size_t pos>
    auto getTuple(std::tuple<Args...> *types, int cur_pos, int_<pos>) {
        int r_pos = line.find(',', cur_pos);
        std::string substring = line.substr(cur_pos, r_pos - cur_pos);
        std::tuple_element_t<pos, std::tuple<Args...>> tmp;
        std::istringstream(substring) >> tmp;
        return std::tuple_cat(std::make_tuple(tmp), getTuple(types, r_pos + 1, int_<pos + 1>()));
    }

public:
    CSVParser() = default;

    CSVParser(std::ifstream& file, int line_skip) {
        SkipLines(file, line_skip);
        std::getline(file, line);
        //std::tuple_element_t<0, std::tuple<Args...>> tup;
        auto tup = new std::tuple<Args...>;
        auto value = getTuple(tup, 0, int_<0>());
        std::cout << value;
    }

};

#endif //CSVPARSER_CSVPARSER_H

