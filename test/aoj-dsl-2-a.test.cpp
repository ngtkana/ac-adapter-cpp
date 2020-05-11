#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_A"

#include <cstddef>
#include <iostream>

#include "../segtree/segtree.hpp"

template <class Value>
struct min_monoid_t {
    using value_type = Value;
    static value_type op(value_type l, value_type r) { return std::min(l, r); }
    static const value_type id() { return std::numeric_limits<Value>::max(); }
};

int main() {
    std::size_t n, q;
    std::cin >> n >> q;

    segtree<min_monoid_t<int>> seg(n, (1ll<<31)-1);

    while (q--) {
        int c;
        std::cin >> c;

        if (c==0) {
            std::size_t i;
            int x;
            std::cin >> i >> x;

            seg.set(i, x);
        }

        if (c==1) {
            std::size_t l, r;
            std::cin >> l >> r;
            r++;

            std::cout << seg.fold(l, r) << '\n';
        }
    }
}
