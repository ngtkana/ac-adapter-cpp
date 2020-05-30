#pragma once

#include "../others/vec.hpp"
#include "../others/cstdint2.hpp"

/*
 * @brief Z algorithm
 * @docs string/z_algorithm.md
 * @see https://snuke.hatenablog.com/entry/2014/12/03/214243
 * @see https://qiita.com/Pro_ktmr/items/16904c9570aa0953bf05
 * @see https://ei1333.github.io/luzhiled/snippets/string/z-algorithm.html
 */

template <class Container, class=typename Container::value_type>
std::vector<usize> z_algorithm (Container const& s) {
    vec<usize> a(s.length());
    if (s.empty()) return a;
    a.at(0) = s.length();
    for (usize i=1, j=1, k; i<s.length(); i=k) {
        for (; j<s.length() && s.at(j-i)==s.at(j); j++);
        a.at(i) = j-i;
        if (j==i) j++;
        for (k=i+1; k<j && k+a.at(k-i)!=j; k++) {
            a.at(k) = std::min(j-k, a.at(k-i));
        }
    }
    return a;
}
