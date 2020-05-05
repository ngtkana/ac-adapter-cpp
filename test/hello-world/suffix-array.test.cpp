#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include "../../string/suffix_array.hpp"

#include <iostream>
#include <cassert>

int main() {

    std::string s = "abracadabra";
    std::vector<std::size_t> result = suffix_array(s);
    std::vector<std::size_t> expected = { 10, 7, 0, 3, 5, 8, 1, 4, 6, 9, 2 };
    assert( result == expected );

    std::vector<long long> v(s.size());
    std::transform( s.begin(), s.end(), v.begin(), [](char c){ return c * 42; });
    result = suffix_array(v);
    assert( result == expected );

    std::cout << "Hello World" << '\n';
}
