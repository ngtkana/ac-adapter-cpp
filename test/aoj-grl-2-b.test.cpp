#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_B"

#include "../bbst/splay_node.hpp"

#include <iostream>
#include <vector>
#include <tuple>

// add-monoid{{{
template <class Value> struct add_monoid_t {
    using value_type = Value;
    static value_type op(value_type l, value_type r) { return l + r; }
    static const value_type id;
};
template <class Value> const typename add_monoid_t<Value>::value_type
add_monoid_t<Value>::id = 0;
/*}}}*/

int main() {
    std::size_t n, q;
    std::cin >> n >> q;

    using splay_node_t = splay_node<add_monoid_t<int>>;

    std::vector<splay_node_t> a(n);
    for (std::size_t i=0; i<n; i++) {
        a.at(i).value = 0;
        if (i<n-1) {
            splay_node_t::merge(&a.at(i), &a.at(i+1));
        }
    }
    splay_node_t *root = &a.back();

    for (std::size_t i=0; i<q; i++) {
        int c;
        std::cin >> c;

        if (c==0) {
            std::size_t i;
            int x;
            std::cin >> i >> x;
            i--;

            root = root->get(i);
            root->set(root->value + x);
        }

        if (c==1) {
            std::size_t l, r;
            std::cin >> l >> r;
            l--;

            int ans;
            std::tie(ans, root) = root->fold(l, r);

            std::cout << ans << '\n';
        }
    }
}
