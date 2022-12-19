#include "TuplePrint.h"
#include "CSVParser.h"
#include "Parser.h"

int main(int argc, char** argv) {
    std::ifstream file("test.csv");
    Parser inp_parser(argc, argv);
    try {
        CSVParser<int, std::string, int> parser(file, 0, inp_parser.column_separator,
                                                inp_parser.lines_separator, inp_parser.shielding);
        for (CSVParser<int, std::string, int> &it: parser) {
            std::cout << it;
        }
    }
    catch (...) {
        std::cout.flush();
        std::cerr << "Wrong input";
    }
    return 0;
}