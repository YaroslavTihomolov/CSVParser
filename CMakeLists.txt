cmake_minimum_required(VERSION 3.20)
project(CSVParser)

set(CMAKE_CXX_STANDARD 17)

add_executable(CSVParser main.cpp TuplePrint.h CSVParser.h Parser.h Parser.cpp)

set(Boost_INCLUDE_DIR C:/MinGW/include/)
set(Boost_LIBRARY_DIR C:/MinGW/lib/)
find_package(Boost COMPONENTS program_options REQUIRED)
target_include_directories(CSVParser PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(CSVParser ${Boost_LIBRARIES})