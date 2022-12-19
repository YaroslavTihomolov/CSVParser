#include "TuplePrint.h"
#include "CSVParser.h"
#include "Parser.h"

int main(int argc, char** argv) {
    std::ifstream file("test.csv");
    Parser inp_parser(argc, argv);
    try {
        CSVParser<int, std::string, float> parser(file, 0, inp_parser.column_separator,
                                                inp_parser.lines_separator, inp_parser.shielding);
        for (CSVParser<int, std::string, float> &it: parser) {
            std::cout << it;
        }
    }
    catch (Exceptions& ex) {
        std::cout.flush();
        std::cerr << ex.what_line() << ":" << ex.what_column() << "    " << ex.what_error();
        return ex.ret_code();
    }
    return 0;
}