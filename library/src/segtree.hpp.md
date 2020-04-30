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


# :heavy_check_mark: segtree

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#eae30ef778b4136fdcc54087b7400598">segtree</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/segtree.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-01 02:03:02+09:00


* see: <a href="https://twitter.com/ngtkana">https://twitter.com/ngtkana</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/src/segtree.test.cpp.html">src/segtree.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/segtree.hpp"



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



/*
 * @title segtree
 * @category segtree
 * @brief so nice
 * @see https://twitter.com/ngtkana
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

