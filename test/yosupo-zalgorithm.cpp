#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../integral/z_algorithm.hpp"

#include <iostream>

int main(){
    std::string s;
    std::cin >> s;

    auto z_array = z_algorhthm(s);

    for (std::size_t i=0; i<s.length(); i++) {
        std::cout << (i ? " " : "") << z_array.at(i);
    }
    std::cout << '\n';
}
