#pragma once
#include <iostream>

template <class T, class U>
struct Pair
{
    T first;
    U second;

    template <class T, class U>
    friend std::ostream& operator<<(std::ostream& os, const Pair<T, U>& p);
};

template <class T, class U>
Pair<T, U> make_pair(const T& first, const U& second)
{
    return { first, second };
}

template <class T, class U>
std::ostream& operator<<(std::ostream& os, const Pair<T, U>& p)
{
    os << p.first << " " << p.second << std::endl;
    return os;
}