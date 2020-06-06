/*
 * @title 剰余多項式 (residual polynomials)
 * @docs integral/residual_polynomials.md
 */

#pragma once

#include <cassert>
#include <cstddef>
#include <utility>
#include <cmath>
#include <type_traits>
#include <iostream>

#include "../others/cstdint2.hpp"
#include "../others/vec.hpp"

template <class Mint>
class resudual_polynomials {
    using mint_type = Mint;

public:
    vec<mint_type> f, qinv, qd;

    resudual_polynomials()=default;
    resudual_polynomials(resudual_polynomials const&)=default;
    resudual_polynomials(resudual_polynomials&&)=default;
    resudual_polynomials& operator=(resudual_polynomials const&)=default;
    resudual_polynomials& operator=(resudual_polynomials&&)=default;
    ~resudual_polynomials()=default;

    resudual_polynomials(vec<mint_type> const& f_)
        : f(f_)
    {
        assert(usize{2} <= f.size());
        qinv.resize(f.size()-1), qd.resize(f.size()-1);
        mint_type x = -f.front().inv(), y = -f.back().inv();
        for (usize i=0; i<qinv.size(); i++) {
            qinv.at(i) = x * f.at(i+1);
            qd.at(i) = y * f.at(i);
        }
    }

    vec<mint_type>& normalize(vec<mint_type>& a) {
        while (a.size() < qd.size()) a.push_back(0);
        while (qd.size() < a.size()) {
            mint_type y = a.back(); a.pop_back();
            for (usize i=0; i<qd.size(); i++) {
                a.at(a.size() - qd.size() + i) += y * qd.at(i);
            }
        }
        return a;
    }

    vec<mint_type> mul(vec<mint_type> a, vec<mint_type> b) {
        normalize(a), normalize(b);
        vec<mint_type> c(qd.size() * 2 - 1);
        for (usize i=0; i<qd.size(); i++) for (usize j=0; j<qd.size(); j++) {
            c.at(i+j) += a.at(i) * b.at(j);
        }
        return normalize(c);
    }

    vec<mint_type> pow(vec<mint_type> a, i64 b) {
        vec<mint_type> ans = {1};
        for(; b; a = mul(a, a), b>>=1) if (b & i64{1}) ans = mul(ans, a);
        return ans;
    }
};

