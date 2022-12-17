#include "TuplePrint.h"
#include "CSVParser.h"

int main() {
    std::ifstream file("test.csv");
    //std::cout << std::make_tuple(5, 30);
    CSVParser<int, std::string, float> parser(file, 1);
    auto t = std::tuple_cat(std::make_tuple(1), std::tuple_cat(std::make_tuple("nikita"), std::make_tuple())) ;
    return 0;
}