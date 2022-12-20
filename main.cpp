#include "TuplePrint.h"
#include "CSVParser.h"
#include "Parser.h"
#include <ctime>

int main(int argc, char** argv) {
    try {
        std::ifstream file("test.csv");
        if (!file.is_open()) throw Exceptions(WRONG_FILE, "WRONG_FILE");
        Parser inp_parser(argc, argv);
        unsigned int start_time =  clock();
        CSVParser<int, std::string, std::string> parser(file, 0, inp_parser.column_separator,
                                                inp_parser.lines_separator, inp_parser.shielding);
        std::ofstream out("out.txt");
        for (CSVParser<int, std::string, std::string> &it: parser) {
            std::cout << it;
        }
        //std::cout << clock() - start_time;
    } catch (Exceptions& ex) {
        std::cout.flush();
        std::cerr << ex;
        return ex.ret_code();
    }
    return 0;
}