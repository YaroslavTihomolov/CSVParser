#ifndef CSVPARSER_PARSER_H
#define CSVPARSER_PARSER_H

#include <iostream>
#include "boost/program_options.hpp"
#include <string>
#include <vector>

namespace po = boost::program_options;

struct Parser {
private:
    po::variables_map vm;
public:
    Parser(int, char**);
    char lines_separator;
    char column_separator;
    char shielding = '"';
};

#endif //CSVPARSER_PARSER_H
