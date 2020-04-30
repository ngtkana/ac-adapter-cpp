#ifndef SEGTREE_HPP
#define SEGTREE_HPP

#include <bits/stdc++.h>

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

#endif // !SEGTREE_HPP

/*
 * @title segtree
 * @category segtree
 * @brief so nice
 * @see https://twitter.com/ngtkana
 */
