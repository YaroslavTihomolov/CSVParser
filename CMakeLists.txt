cmake_minimum_required(VERSION 3.20)
project(CSVParser)

set(CMAKE_CXX_STANDARD 14)

add_executable(CSVParser main.cpp TuplePrint.h CSVParser.h CSVParser.cpp)
