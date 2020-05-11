/*
 * @title セグメント木 (segtree)
 * @docs segtree/segtree.md
 */

#pragma once

#include <cassert>
#include <cstddef>
#include <vector>
#include <algorithm>

template <class Monoid>
struct segtree
{
    using value_type = typename Monoid::value_type;

    std::vector<value_type> table;

    segtree()=default;
    segtree(segtree const&)=default;
    segtree(segtree&&)=default;
    segtree&operator=(segtree const&)=default;
    segtree&operator=(segtree&&)=default;

    segtree(std::size_t n, value_type init=Monoid::id())
        : table(2*n, init) {}

    void resize(std::size_t n, value_type init=Monoid::id()) {
        assert(table.empty());
        table.resize(2*n, init);
    }

    void lazy_set(std::size_t i, value_type x) {
        table.at(i + size()) = x;
    }

    void build() {
        for (std::size_t i=size()-1; i; i--) {
            table.at(i) = Monoid::op(table.at(2*i), table.at(2*i+1));
        }
    }

    std::size_t size() const { return table.size() / 2; }

    value_type fold(std::size_t l, std::size_t r) const {
        value_type fl = Monoid::id();
        value_type fr = Monoid::id();

        for(l+=size(),r+=size();l<r;l>>=1,r>>=1){
            if(l&1u) fl=Monoid::op(fl, table.at(l++));
            if(r&1u) fr=Monoid::op(fr, table.at(--r));
        }

        return Monoid::op(fl, fr);
    }

    value_type get(std::size_t i) const { return table.at(size() + i); }

    std::vector<value_type> to_vec() const {
        std::vector<value_type> ret(size());
        std::copy(table.begin()+size(), table.end(), ret.begin());
        return ret;
    }

    void set(std::size_t i, value_type x) {
        assert(i < size());
        i+=size();
        table.at(i) = x;
        for (i>>=1; i; i>>=1) {
            table.at(i) = Monoid::op(table.at(2*i), table.at(2*i+1));
        }
    }

    void add(std::size_t i, value_type x) { set(i, get(i) + x); }
    void sub(std::size_t i, value_type x) { set(i, get(i) - x); }
    void mul(std::size_t i, value_type x) { set(i, get(i) * x); }
    void div(std::size_t i, value_type x) { set(i, get(i) / x); }

    template <class F> void map(std::size_t i, F const& f) { set(i, f(get(i))); }
};
