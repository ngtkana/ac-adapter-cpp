#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_A"

#include "../bbst/splay_node.hpp"

#include <iostream>
#include <vector>
#include <tuple>
#include <limits>

// min-monoid{{{
template <class Value> struct min_monoid_t {
    using value_type = Value;
    static value_type op(value_type l, value_type r) { return std::min(l, r); }
    static const value_type id;
};
template <class Value> const typename min_monoid_t<Value>::value_type
min_monoid_t<Value>::id = std::numeric_limits<min_monoid_t<Value>::value_type>::max();
/*}}}*/

int main() {
    std::size_t n, q;
    std::cin >> n >> q;

    using splay_node_t = splay_node<min_monoid_t<int>>;
    int inf = min_monoid_t<int>::id;

    std::vector<splay_node_t> a(n);
    for (std::size_t i=0; i<n; i++) {
        a.at(i).set(inf);
        if (i<n-1) {
            splay_node_t::merge(&a.at(i), &a.at(i+1));
        }
    }
    splay_node_t *root = &a.back();

    while (q--) {
        int c;
        std::cin >> c;

        if (c==0) {
            std::size_t i;
            int x;
            std::cin >> i >> x;

            root = root->get(i);
            root->set(x);
        }

        if (c==1) {
            std::size_t l, r;
            std::cin >> l >> r;
            r++;

            int ans;
            std::tie(ans, root) = root->fold(l, r);

            if (ans==inf) {
                ans = (1ll << 31) - 1;
            }

            std::cout << ans << '\n';
        }
    }
}
