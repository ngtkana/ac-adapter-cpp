#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_D"


#include <cstddef>
#include <type_traits>
#include <utility>
#include <algorithm>
#include <vector>
#include <iostream>

#include "../graph/tree/hl_decomposition.hpp"

template <class Monoid> struct segtree{
    // a type alias
    using value_type = typename Monoid::value_type;

    // member variables
    std::vector<value_type>table;

    // trivial constructors
    segtree()=default;
    segtree(segtree const&)=default;
    segtree(segtree&&)=default;
    segtree&operator=(segtree const&)=default;
    segtree&operator=(segtree&&)=default;

    // a non-trivial constructor
    segtree(std::size_t n) : table(2*n, Monoid::id) {}

    // resize
    void resize(std::size_t n) {
        assert(table.empty());
        table.resize(2*n);
    }

    // size
    std::size_t size() const { return table.size() / 2; }

    // fold
    value_type fold(std::size_t l, std::size_t r) const {
        value_type fl = Monoid::id;
        value_type fr = Monoid::id;

        for(l+=size(),r+=size();l<r;l>>=1,r>>=1){
            if(l&1u) fl=Monoid::op(fl, table.at(l++));
            if(r&1u) fr=Monoid::op(fr, table.at(--r));
        }

        return Monoid::op(fl, fr);
    }

    // set
    void set(std::size_t i, value_type x) {
        assert(0 <= i);
        assert(i < size());

        i+=size();
        table.at(i) = x;

        for(i>>=1;i;i>>=1){ table.at(i) = Monoid::op(table.at(2*i), table.at(2*i+1)); }
    }

    // lazy_set
    void lazy_set(std::size_t i, value_type x) {
        assert(0 <= i);
        assert(i < size());

        i+=size();
        table.at(i) = x;
    }

    // map
    template <class F>
        void map(std::size_t i, F const& f) { set(i, f(at(i))); }

    // build
    void build() {
        for(std::size_t i=size()-1;i;i--){ table.at(i) = Monoid::op(table.at(2*i), table.at(2*i+1)); }
    }

    // at
    value_type at(std::size_t i) const { return table.at(size() + i); }

    // to_vec
    std::vector<value_type> to_vec() const {
        std::vector<value_type> ret(size());
        std::copy(table.begin()+size(), table.end(), ret.begin());
        return ret;
    }
};

template <class Value> struct add_monoid_t {
    using value_type = Value;
    static value_type op(value_type l, value_type r) { return l + r; }
    static const value_type id;
};
template <class Value> const typename add_monoid_t<Value>::value_type
add_monoid_t<Value>::id = 0;

int main(){
    std::size_t n;
    std::cin >> n;

    std::size_t root = 0;

    std::vector<std::size_t> prt(n);
    hl_decomposition hld(n);
    for (std::size_t i=0; i<n ;i++) {
        std::size_t k;
        std::cin >> k;
        while (k--) {
            std::size_t j;
            std::cin >> j;
            hld.insert(i, j);
            prt.at(j) = i;
        }
    }
    hld.build(0);

    std::size_t q;
    std::cin >> q;
    auto seg = segtree<add_monoid_t<unsigned long long>>(n);
    while (q--) {
        int c;
        std::cin >> c;

        if (c==0) {
            std::size_t u;
            unsigned long long w;
            std::cin >> u >> w;

            seg.set(hld.vid.at(u), seg.at(hld.vid.at(u)) + w);
        }

        if (c==1) {
            std::size_t u, v;
            std::cin >> u;
            v = root;

            unsigned long long ans = 0;

            while (u!=v) {
                if (hld.vid.at(u) > hld.vid.at(v)) {
                    std::swap(u, v);
                }
                if (hld.head.at(u) == hld.head.at(v)) {
                    ans += seg.fold(hld.vid.at(u)+1, hld.vid.at(v)+1);
                    break;
                }
                ans += seg.fold(hld.vid.at(hld.head.at(v)), hld.vid.at(v)+1);
                v = prt.at(hld.head.at(v));
            }

            std::cout << ans << '\n';
        }
    }
}


