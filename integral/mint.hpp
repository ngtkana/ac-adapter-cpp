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

    static value_type& mod() { return ModType::value; }

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
    mint  operator++(int) { mint this_=*this; ++*this; return this_; }
    mint  operator--(int) { mint this_=*this; --*this; return this_; }

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

    mint add(mint y) { mint ans=*this; return ans.add_assign(y); }
    mint sub(mint y) { mint ans=*this; return ans.sub_assign(y); }
    mint mul(mint y) { mint ans=*this; return ans.mul_assign(y); }
    mint div(mint y) { mint ans=*this; return ans.div_assign(y); }
    mint inv()       { mint ans=*this; return ans.inv_assign(); }
    mint pow(unsigned long long y) { return pow(*this, y); }

    template <class F> mint map(F const& f){
        value=f(value);
        return *this;
    }
};

template <class T> std::istream&
operator>>(std::istream& is, modint<T>& x)
{
    typename modint<T>::value_type y;
    is >> y;
    x = modint<T>{ y };
    return is;
}
template <class T> std::ostream&
operator<<(std::ostream& os, modint<T> x)
{
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

struct mod_type {
    using value_type = i32;
    static value_type value;
};

mod_type::value_type mod_type::value;

using mint = modint<mod_type>;
