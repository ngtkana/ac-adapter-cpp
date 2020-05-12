#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/1/ITP2_1_A"

#include <cstddef>
#include <iostream>

#include "../others/cstdint2.hpp"
#include "../bbst/splay_tree.hpp"

template <class Value> struct add_monoid_t {
    using value_type = Value;
    static value_type op(value_type l, value_type r) { return l + r; }
    static const value_type id() { return 0; }
};

int main(){

    splay_tree<add_monoid_t<i32>> sp;

    usize q;
    std::cin >> q;
    while (q--) {
        u32 c;
        std::cin >> c;

        if (c==0) {
            i32 x;
            std::cin >> x;

            sp.push_back(x);
        }

        if (c==1) {
            usize i;
            std::cin >> i;

            std::cout << sp.get(i) << '\n';
        }

        if (c==2) {
            sp.pop_back();
        }
    }
}

