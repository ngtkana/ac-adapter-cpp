#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <random>

#include "cstdint2.hpp"
#include "vec.hpp"
#include "permutations.hpp"

int main() {
    std::mt19937 mt{ std::random_device{}()} ;

    auto iota = [](usize n) {
        vec<usize> a(n);
        std::iota(a.begin(), a.end(), 0u);
        return a;
    };

    auto generate_random_permutation = [&mt, &iota] (usize n) {
        vec<usize> a = iota(n);
        std::shuffle(a.begin(), a.end(), mt);
        return a;
    };

    for (usize ph=0; ph<20; ph++) {
        usize n = 50;
        auto i = iota(n);
        auto a = generate_random_permutation(n);
        auto b = generate_random_permutation(n);

        assert(i == permutations::mul(a, permutations::inv(a)));

        auto ba = permutations::mul(b, a);
        permutations::mul_assign_from_the_right(a, b);
        assert(ba == a);
    }

    i32 x, y;
    std::cin >> x >> y;
    std::cout << x + y << '\n';
}
