#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_4_B"

#include <cstddef>
#include <iostream>

#include "../bbst/splay_tree.hpp"

template <class Value> struct add_monoid_t {
    using value_type = Value;
    static value_type op(value_type l, value_type r) { return l + r; }
    static const value_type id() { return 0; }
};

int main(){
    std::size_t n;
    std::cin >> n;

    splay_tree<add_monoid_t<int>> sp(n);
    for (std::size_t i=0; i<n; i++) {
        int x;
        std::cin >> x;
        sp.set(i, x);
    }

    unsigned int ans = 0;
    std::size_t q;
    std::cin >> q;
    while (q--) {
        int x;
        std::cin >> x;

        std::size_t i = sp.lower_bound(x);
        ans += i<n && sp.get(i)==x;
    }
    std::cout << ans << '\n';
}
