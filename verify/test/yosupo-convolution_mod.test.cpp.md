---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: test/yosupo-convolution_mod.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo-convolution_mod.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-06-06 02:59:26+09:00


* see: <a href="https://judge.yosupo.jp/problem/convolution_mod">https://judge.yosupo.jp/problem/convolution_mod</a>


## Depends on

* :heavy_check_mark: <a href="../../library/integral/mint.hpp.html">integral/mint.hpp</a>
* :heavy_check_mark: <a href="../../library/integral/nt_trsf.hpp.html">NTT</a>
* :heavy_check_mark: <a href="../../library/others/cstdint2.hpp.html">others/cstdint2.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../integral/nt_trsf.hpp"

#include <iostream>
#include <cassert>

using mint = modint<std::integral_constant<i32, 998244353>>;

int main(){
    nt_trsf<mint> ntt;

    std::size_t n, m;
    std::cin >> n >> m;

    std::vector<mint> a(n), b(m);
    for (mint& x: a) std::cin >> x;
    for (mint& x: b) std::cin >> x;

    auto c = ntt.multiply(a, b);
    c.resize(n+m-1);

    for (std::size_t i=0; i<c.size(); i++) {
        std::cout << (i?" ":"") << c.at(i);
    }
    std::cout << '\n';
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo-convolution_mod.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#line 2 "integral/nt_trsf.hpp"

#line 2 "integral/mint.hpp"

#include <cassert>
#include <cstddef>
#include <utility>
#include <cmath>
#include <type_traits>
#include <iostream>

#line 2 "others/cstdint2.hpp"

#include <cstdint>

using i32 = std::int_least32_t;
using i64 = std::int_least64_t;
using u32 = std::uint_least32_t;
using u64 = std::uint_least64_t;
using usize = std::size_t;
#line 11 "integral/mint.hpp"

template <class ModType> struct modint {
    using value_type = typename ModType::value_type;
    using mint = modint<ModType>;
    using mod_type = ModType;

    static value_type mod() { return ModType::value; }

    private:
    static value_type inverse(value_type x) {
        value_type y=1,u=mod(),v=0;
        while(x){
            value_type q=u/x;
            u-=q*x; std::swap(x,u);
            v-=q*y; std::swap(y,v);
        }
        assert(x==0 && std::abs(y)==mod() && std::abs(u)==1 && std::abs(v)<mod());
        return v<0?v+mod():v;
    }

    public:
    // the member variable
    value_type value;

    // constructors
    modint()=default;
    modint(modint const&)=default;
    modint(modint&&)=default;
    modint& operator=(modint const&)=default;
    modint& operator=(modint&&)=default;
    ~modint()=default;

    template <class T> modint(T t) : value([t] () mutable {
            if ( t <= -static_cast<T>(mod()) || static_cast<T>(mod()) <= t ) t %= mod();
            return t < 0 ? t + mod() : t;
            }()) {}

    // operators
    mint& operator+= (mint y) {
        value += y.value;
        if (mod() <= value) value -= mod();
        return *this;
    }

    mint& operator-= (mint y) {
        value -= y.value;
        if ( value < 0 ) value += mod();
        return *this;
    }

    mint& operator*= (mint y) {
        value = (long long)value * y.value % mod();
        return *this;
    }

    mint& operator/= (mint y) {
        value = (long long)value * inverse(y.value) % mod();
        return *this;
    }

    mint& operator++() { return *this+=1; }
    mint& operator--() { return *this-=1; }
    mint operator++(int) { mint this_=*this; ++*this; return this_; }
    mint operator--(int) { mint this_=*this; --*this; return this_; }
    mint operator-() const { return 0 - *this; }

    // static member functions
    static mint inv(mint x) { return inverse(x.value); }

    static mint m1pow(long long y) { return y%2?-1:1; }

    static mint pow(mint x, unsigned long long y) {
        mint ans=1;
        for(;y;y>>=1){
            if(y&1ull) ans*=x;
            x*=x;
        }
        return ans;
    }

    // non-member functions
    mint& add_assign(mint y) { return *this+=y; }
    mint& sub_assign(mint y) { return *this-=y; }
    mint& mul_assign(mint y) { return *this*=y; }
    mint& div_assign(mint y) { return *this/=y; }
    mint& inv_assign()       { return *this = inv(*this); }
    mint& pow_assign(unsigned long long y){ return *this = pow(*this, y); }

    mint add(mint y) const { mint ans=*this; return ans.add_assign(y); }
    mint sub(mint y) const { mint ans=*this; return ans.sub_assign(y); }
    mint mul(mint y) const { mint ans=*this; return ans.mul_assign(y); }
    mint div(mint y) const { mint ans=*this; return ans.div_assign(y); }
    mint inv()       const { mint ans=*this; return ans.inv_assign(); }
    mint pow(unsigned long long y) const { return pow(*this, y); }
    mint square(mint x) const { return *this * *this; }
    mint cube(mint x) const { return *this * *this * *this; }

    template <class F> mint map(F const& f){
        value=f(value);
        return *this;
    }
};

template <class T> std::istream&
operator>>(std::istream& is, modint<T>& x) {
    typename modint<T>::value_type y;
    is >> y;
    x = modint<T>{ y };
    return is;
}
template <class T> std::ostream&
operator<<(std::ostream& os, modint<T> x) {
    return os << x.value;
}

template <class T> modint<T> operator+(modint<T> x, modint<T> y) { return x+=y; }
template <class T> modint<T> operator-(modint<T> x, modint<T> y) { return x-=y; }
template <class T> modint<T> operator*(modint<T> x, modint<T> y) { return x*=y; }
template <class T> modint<T> operator/(modint<T> x, modint<T> y) { return x/=y; }
template <class T> bool operator==(modint<T> x, modint<T> y) { return x.value==y.value; }
template <class T> bool operator!=(modint<T> x, modint<T> y) { return x.value!=y.value; }

template <class T, class U> modint<T> operator+(modint<T> x, U y) { return x+modint<T>(y); }
template <class T, class U> modint<T> operator-(modint<T> x, U y) { return x-modint<T>(y); }
template <class T, class U> modint<T> operator*(modint<T> x, U y) { return x*modint<T>(y); }
template <class T, class U> modint<T> operator/(modint<T> x, U y) { return x/modint<T>(y); }
template <class T, class U> bool operator==(modint<T> x, U y) { return x==modint<T>(y); }
template <class T, class U> bool operator!=(modint<T> x, U y) { return x!=modint<T>(y); }

template <class T, class U> modint<T> operator+(U x, modint<T> y) { return modint<T>(x)+y; }
template <class T, class U> modint<T> operator-(U x, modint<T> y) { return modint<T>(x)-y; }
template <class T, class U> modint<T> operator*(U x, modint<T> y) { return modint<T>(x)*y; }
template <class T, class U> modint<T> operator/(U x, modint<T> y) { return modint<T>(x)/y; }
template <class T, class U> bool operator==(U x, modint<T> y) { return modint<T>(x)==y; }
template <class T, class U> bool operator!=(U x, modint<T> y) { return modint<T>(x)!=y; }
#line 4 "integral/nt_trsf.hpp"

#include <array>
#include <vector>
#line 8 "integral/nt_trsf.hpp"
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
#line 4 "test/yosupo-convolution_mod.test.cpp"

#line 7 "test/yosupo-convolution_mod.test.cpp"

using mint = modint<std::integral_constant<i32, 998244353>>;

int main(){
    nt_trsf<mint> ntt;

    std::size_t n, m;
    std::cin >> n >> m;

    std::vector<mint> a(n), b(m);
    for (mint& x: a) std::cin >> x;
    for (mint& x: b) std::cin >> x;

    auto c = ntt.multiply(a, b);
    c.resize(n+m-1);

    for (std::size_t i=0; i<c.size(); i++) {
        std::cout << (i?" ":"") << c.at(i);
    }
    std::cout << '\n';
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

