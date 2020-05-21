#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <iostream>
#include <tuple>

#include "cstdint2.hpp"
#include "vec.hpp"
#include "cartesian_tree.hpp"

int main() {
    vec<i32> a = {1, 1, 4, 3};

    usize r;
    vec<vec<usize>> g;
    std::tie(r, g) = cartesian_tree(a);
    std::tie(r, g) = cartesian_tree(a, std::greater<>{});

    i32 x, y;
    std::cin >> x >> y;
    std::cout << x + y << '\n';
}
