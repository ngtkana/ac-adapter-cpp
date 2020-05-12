#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_1_B"

#include <iostream>
#include <limits>

#include "../others/cstdint2.hpp"
#include "../bbst/splay_tree.hpp"

template <class Value> struct min_monoid_t {
    using value_type = Value;
    static value_type op(value_type l, value_type r) { return std::min(l, r); }
    static const value_type id() { return std::numeric_limits<Value>::max(); }
};

int main(){
    splay_tree<min_monoid_t<i32>> sp;

    usize q;
    std::cin >> q;
    while (q--) {
        i32 c;
        std::cin >> c;

        if (c==0) {
            i32 d, x;
            std::cin >> d >> x;

            if (d==0) {
                sp.push_front(x);
            }
            if (d==1) {
                sp.push_back(x);
            }
        }

        if (c==1) {
            usize i;
            std::cin >> i;

            std::cout << sp.get(i) << '\n';
        }

        if (c==2) {
            i32 d;
            std::cin >> d;

            if (d==0) {
                sp.pop_front();
            }
            if (d==1) {
                sp.pop_back();
            }
        }
    }
}
