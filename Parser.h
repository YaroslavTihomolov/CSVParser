#ifndef CSVPARSER_PARSER_H
#define CSVPARSER_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include "boost/program_options.hpp"
#include "Exceptions.h"

namespace po = boost::program_options;

struct Parser {
private:
    po::variables_map vm;
public:
    Parser(int, char**);
    char lines_separator;
    char column_separator{};
    char shielding = '"';
};

#endif //CSVPARSER_PARSER_H
