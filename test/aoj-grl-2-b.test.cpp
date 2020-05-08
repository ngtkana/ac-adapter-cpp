#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_B"

#include "../bbst/splay_tree.hpp"

#include <iostream>
#include <vector>
#include <tuple>

// add-monoid{{{
template <class Value> struct add_monoid_t {
    using value_type = Value;
    static value_type op(value_type l, value_type r) { return l + r; }
    static const value_type id() { return 0; };
};
/*}}}*/

int main() {
    std::size_t n, q;
    std::cin >> n >> q;

    splay_tree<add_monoid_t<int>> sp(n);

    for (std::size_t i=0; i<q; i++) {
        int c;
        std::cin >> c;

        if (c==0) {
            std::size_t i;
            int x;
            std::cin >> i >> x;
            i--;

            sp.set(i, sp.get(i) + x);
        }

        if (c==1) {
            std::size_t l, r;
            std::cin >> l >> r;
            l--;

            std::cout << sp.fold(l, r) << '\n';
        }
    }
}
