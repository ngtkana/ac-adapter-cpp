#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A"

#include "segtree.hpp"

#include <iostream>

template <class Value> struct min_monoid_t {
    using value_type = Value;
    static value_type op(value_type l, value_type r) { return std::min(l, r); }
    static const value_type id;
};
template <class Value> const typename min_monoid_t<Value>::value_type
min_monoid_t<Value>::id = std::numeric_limits<min_monoid_t<Value>::value_type>::max();

int main(){
    int n, q;
    std::cin >> n >> q;

    auto seg = segtree<min_monoid_t<int>>(n);
    int inf = min_monoid_t<int>::id;

    while (q--) {
        int c;
        std::cin >> c;

        if (c == 0) {
            int i, x;
            std::cin >> i >> x;

            seg.set(i, x);
        }

        if (c == 1) {
            int l, r;
            std::cin >> l >> r;
            r++;

            int ans = seg.fold(l, r);
            if (ans == inf) ans = (1ll << 31) - 1;

            std::cout << ans << '\n';
        }
    }
}
