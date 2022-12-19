#include "TuplePrint.h"
#include "CSVParser.h"

int main() {
    std::ifstream file("test.csv");
    CSVParser<int, std::string, int> parser(file, 0);
    for (auto it = parser.begin(); it != parser.end(); ++it)
    for (CSVParser<int, std::string, int>& it : parser) {
        std::cout << it;
    }
    return 0;
}