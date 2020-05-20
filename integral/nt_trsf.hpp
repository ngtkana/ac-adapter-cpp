#pragma once

#include "mint.hpp"

#include <array>
#include <vector>
#include <cstddef>
#include <limits>

template <class Mint>
struct nt_trsf {
    using mint_type = Mint;
    using value_type = typename mint_type::value_type;

    std::array<std::vector<mint_type>, 2> table;

    nt_trsf()
    {
        assert(3<=mod() && mod()%2);
        std::size_t period = (mod()-1) & (-mod()+1);
        std::size_t lg = std::numeric_limits<std::size_t>::digits - __builtin_clzll(period) - 1;

        mint_type root = 2;
        for (; root.pow(period)!=1 || root.pow(period>>1)==1; root++);

        for (std::size_t i=0; i<2; i++) {
            auto&& v = table.at(i);
            v.resize(lg+1);
            v.back() = i==0 ? root : root.inv();

            for (std::size_t j=lg; j; j--){
                v.at(j-1) = v.at(j) * v.at(j);
            }
        }
    }

    nt_trsf(nt_trsf const&)=default;
    nt_trsf(nt_trsf&&)=default;
    nt_trsf& operator=(nt_trsf const&)=default;
    nt_trsf& operator=(nt_trsf&&)=default;
    ~nt_trsf()=default;

    static value_type mod() { return mint_type::mod(); }

    static bool is_pow_of_2(std::size_t n) { return (n & (n-1)) == 0; }

    std::vector<mint_type>
    transform(std::vector<mint_type> const& a, std::size_t direction) const
    {
        std::size_t n = a.size();
        assert(is_pow_of_2(n));

        // ビット反転
        // FIXME: これは、正変換に共役作用されることで省略可能です。
        std::vector<mint_type> b(n);
        for (std::size_t i=0, j=0, d; i<n; i++) {
            b.at(j) = a.at(i);
            for (d=n>>1; j&d; d>>=1) j^=d;
            j^=d;
        }

        // バタフライ演算
        for (std::size_t i=1, d=1, D=1; d<n; i++, d<<=1, D=D<<1|1u) {
            mint_type w = 1;
            for (std::size_t j=0, k=d; k<n; j++, k++) {
                if ((j&D)==d) {
                    j+=d, k+=d;
                    assert(w == -1);
                    w = 1;
                }
                mint_type x = b.at(j), y = b.at(k);
                b.at(j) = x + w * y;
                b.at(k) = x - w * y;
                w *= table.at(direction).at(i);
            }
        }
        return b;
    }

    std::vector<mint_type>
    multiply(std::vector<mint_type> a, std::vector<mint_type> b) const
    {
        std::size_t sz = a.size() + b.size();
        for (; !is_pow_of_2(sz); sz++);
        for (; a.size()<sz; a.emplace_back(0));
        for (; b.size()<sz; b.emplace_back(0));
        assert(a.size()==b.size());

        a = transform(a, 0u);
        b = transform(b, 0u);
        for (std::size_t i=0; i<sz; i++) {
            a.at(i) *= b.at(i);
        }
        a = transform(a, 1u);

        for (; !a.empty() && a.back() == 0; a.pop_back());

        mint_type scale = mint_type::inv(sz);
        for (mint_type& x : a) x *= scale;
        return a;
    }
};

/*
 * @title NTT
 * @docs docs/integral/ntt_trsf.md
 */
