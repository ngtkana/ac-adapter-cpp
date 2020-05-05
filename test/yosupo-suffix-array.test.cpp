#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "../string/suffix_array.hpp"

#include <iostream>
#include <cassert>

int main(){
    std::string s;
    std::cin >> s;

    std::vector<std::size_t> sa = suffix_array(s);

    std::vector<long long> v(s.size());
    std::transform(s.begin(), s.end(), v.begin(), [](char c){ return c * 42; });
    assert( sa == suffix_array(v) );

    for (std::size_t i=0; i<s.size(); i++) {
        std::cout << (i?" ":"") << sa.at(i);
    }
    std::cout << '\n';
}
