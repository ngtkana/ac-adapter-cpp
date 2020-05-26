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

    static u64 merge_sort(vec<usize>& a) {
        if (a.size() <= 1u) return 0u;
        vec<usize> b(a.begin(), a.begin()+a.size()/2), c(a.begin()+a.size()/2, a.end());
        u64 ans = merge_sort(b) + merge_sort(c);
        for (usize i=0, j=0; i<b.size() || j<c.size(); ) {
            if (j==c.size() || (i<b.size() && b.at(i) < c.at(j))) {
                a.at(i+j) = b.at(i);
                i++;
            } else {
                ans += b.size() - i;
                a.at(i+j) = c.at(j);
                j++;
            }
        }
        return ans;
    }

    static u64 inversion_number(vec<usize> a) {
        return merge_sort(a);
    }
};

#endif

