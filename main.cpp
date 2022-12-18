#include "TuplePrint.h"
#include "CSVParser.h"

int main() {
    std::ifstream file("test.csv");
    CSVParser<int, std::string> parser(file, 0);
    for (CSVParser<int, std::string>& it : parser) {
        std::cout << it;
    }
    return 0;
}