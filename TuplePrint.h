//
// Created by я on 15.12.2022.
//

#ifndef CSVPARSER_TUPLEPRINT_H
#define CSVPARSER_TUPLEPRINT_H

#include <iostream>
#include <tuple>
#include <fstream>

template<std::size_t>
struct int_ { };

/*template<typename... Args> struct tuple;

template<typename Head, typename... Tail>
auto PrintTuple(std::ostream& out, std::tuple<Tail...> const& t) {
    H
}

template<class... Tail>
auto operator<<(std::ostream& out, std::tuple<Tail...> const& t) {
    out << "{";
    PrintTuple(out, t, int_<sizeof...(Tail)>());
    return out << "}";
}

template<> struct tuple<> {};*/

/*template <class... Args>
auto operator<<(std::ostream& out, std::tuple<Args...> const& t) {
    return out << std::get<std::tuple_size<Tuple>::value - 1>(t);
}*/


/*template <class Tuple>
std::ostream& PrintTuple(std::ostream& out, const Tuple& t, int_<1>) {
    return out << std::get<std::tuple_size<Tuple>::value - 1>(t);
}

template <class Tuple, std::size_t pos>
std::ostream& PrintTuple(std::ostream& out, const Tuple& t, int_<pos>) {
    out << std::get<std::tuple_size<Tuple>::value-pos>(t) << ", ";
    return PrintTuple(out, t, int_<pos - 1>());
}

template<class... Args>
std::ostream& operator<<(std::ostream& out, const std::tuple<Args...>& t) {
    out << "{";
    PrintTuple(out, t, int_<sizeof...(Args)>());
    return out << "}";
}*/

template<class Os, class... Args>
Os &operator<<(Os &os, const std::tuple<Args...> &t) {
    os << "{ ";
    std::apply([&](auto &&arg, auto &&... args) {
        os << arg;
        ((os << ", " << args), ...);
    }, t);
    return os << " }";
}

#endif //CSVPARSER_TUPLEPRINT_H
