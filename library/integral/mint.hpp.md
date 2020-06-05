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


# :heavy_check_mark: integral/mint.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#25aa2761448ea05599418ee93dd1d5c5">integral</a>
* <a href="{{ site.github.repository_url }}/blob/master/integral/mint.hpp">View this file on GitHub</a>
    - Last commit date: 2020-06-06 02:59:26+09:00




## Depends on

* :heavy_check_mark: <a href="../others/cstdint2.hpp.html">others/cstdint2.hpp</a>


## Required by

* :heavy_check_mark: <a href="nt_trsf.hpp.html">NTT</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/integral/residual_polynomials.test.cpp.html">integral/residual_polynomials.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo-convolution_mod.test.cpp.html">test/yosupo-convolution_mod.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cassert>
#include <cstddef>
#include <utility>
#include <cmath>
#include <type_traits>
#include <iostream>

#include "../others/cstdint2.hpp"

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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

