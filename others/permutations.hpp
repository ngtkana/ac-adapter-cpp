/*
 * @title 置換 (permutations)
 * @docs others/permutations.md
 */
#ifndef OTHERS_PERMUPTATIONS_HPP
#define OTHERS_PERMUPTATIONS_HPP

#include <cassert>
#include <algorithm>
#include <numeric>

#include "cstdint2.hpp"
#include "vec.hpp"

struct permutations {
    static vec<usize>& mul_assign_from_the_right(vec<usize>& a, vec<usize> const& b) {
        for (usize i=0; i<a.size(); i++) {
            a.at(i) = b.at(a.at(i));
        }
        return a;
    }

    static vec<usize> mul(vec<usize> const& a, vec<usize> const& b) {
        assert(a.size()==b.size());
        vec<usize> ans(a.size());
        for (usize i=0; i<a.size(); i++) {
            ans.at(i) = a.at(b.at(i));
        }
        return ans;
    }

    static vec<usize> inv(vec<usize> const& a) {
        vec<usize> ans(a.size());
        for (usize i=0; i<a.size(); i++) {
            ans.at(a.at(i)) = i;
        }
        return ans;
    }

    template <class T>
    static vec<usize> pow(vec<usize> a, T b) {
        vec<usize> ans(a.size());
        std::iota(ans.begin(), ans.end(), 0u);
        for (; b; b>>=1) {
            if (b&1) ans = mul(ans, a);
            a = mul(a, a);
        }
        return ans;
    }
};

#endif

