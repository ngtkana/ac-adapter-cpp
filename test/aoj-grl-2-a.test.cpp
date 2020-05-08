#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_A"

#include "../bbst/splay_tree.hpp"

#include <iostream>
#include <vector>
#include <tuple>
#include <limits>

// min-monoid{{{
template <class Value> struct min_monoid_t {
    using value_type = Value;
    static value_type op(value_type l, value_type r) { return std::min(l, r); }
    static const value_type id() { return std::numeric_limits<value_type>::max(); }
};
/*}}}*/

int main() {
    std::size_t n, q;
    std::cin >> n >> q;

    std::vector<int>a(n, (1ll << 31) - 1);
    splay_tree<min_monoid_t<int>> sp(a);

    while (q--) {
        int c;
        std::cin >> c;

        if (c==0) {
            std::size_t i;
            int x;
            std::cin >> i >> x;

            sp.set(i, x);
        }

        if (c==1) {
            std::size_t l, r;
            std::cin >> l >> r;
            r++;

            std::cout << sp.fold(l, r) << '\n';
        }
    }
}
