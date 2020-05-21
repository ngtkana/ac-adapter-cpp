/*
 * @title カルテシアン木 (Cartesian Tree)
 * @docs others/cartesian_tree.hpp
 */

#include <utility>
#include <functional>

#include "cstdint2.hpp"
#include "vec.hpp"

template <class T, class Comp=std::less<T>>
auto cartesian_tree(vec<T> const& a, Comp const& comp={}) {
    usize n = a.size();
    vec<T> stack;
    vec<usize> p(n, n);
    for (usize i=0; i<n; i++) {
        usize j = n;
        while (!stack.empty() && comp(a.at(i), a.at(stack.back()))) {
            j = stack.back();
            stack.pop_back();
        }
        if (j!=n) {
            p.at(j) = i;
        }
        if (!stack.empty()) {
            p.at(i) = stack.back();
        }
        stack.push_back(i);
    }

    usize root = n;
    vec<vec<usize>> g(n);
    for (usize i=0; i<n; i++) {
        if (p.at(i)==n) {
            root = i;
        } else {
            g.at(p.at(i)).push_back(i);
        }
    }
    return std::make_pair(root, g);
}
