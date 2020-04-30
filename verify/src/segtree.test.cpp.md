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


# :heavy_check_mark: src/segtree.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#25d902c24283ab8cfbac54dfa101ad31">src</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/segtree.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-01 02:26:10+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A</a>


## Depends on

* :heavy_check_mark: <a href="../../library/src/segtree.hpp.html">segtree</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A"

#include "segtree.hpp"

#include <iostream>

template <class Value> struct min_monoid_t {
    using value_type = Value;
    static value_type op(value_type l, value_type r) { return std::min(l, r); }
    static const value_type id;
};
template <class Value> const typename min_monoid_t<Value>::value_type
min_monoid_t<Value>::id = std::numeric_limits<min_monoid_t<Value>::value_type>::max();

int main(){
    int n, q;
    std::cin >> n >> q;

    auto seg = segtree<min_monoid_t<int>>(n);
    int inf = min_monoid_t<int>::id;

    while (q--) {
        int c;
        std::cin >> c;

        if (c == 0) {
            int i, x;
            std::cin >> i >> x;

            seg.set(i, x);
        }

        if (c == 1) {
            int l, r;
            std::cin >> l >> r;
            r++;

            int ans = seg.fold(l, r);
            if (ans == inf) ans = (1ll << 31) - 1;

            std::cout << ans << '\n';
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/segtree.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A"

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
 * @docs docs/segtree.md
 */
#line 4 "src/segtree.test.cpp"

#line 6 "src/segtree.test.cpp"

template <class Value> struct min_monoid_t {
    using value_type = Value;
    static value_type op(value_type l, value_type r) { return std::min(l, r); }
    static const value_type id;
};
template <class Value> const typename min_monoid_t<Value>::value_type
min_monoid_t<Value>::id = std::numeric_limits<min_monoid_t<Value>::value_type>::max();

int main(){
    int n, q;
    std::cin >> n >> q;

    auto seg = segtree<min_monoid_t<int>>(n);
    int inf = min_monoid_t<int>::id;

    while (q--) {
        int c;
        std::cin >> c;

        if (c == 0) {
            int i, x;
            std::cin >> i >> x;

            seg.set(i, x);
        }

        if (c == 1) {
            int l, r;
            std::cin >> l >> r;
            r++;

            int ans = seg.fold(l, r);
            if (ans == inf) ans = (1ll << 31) - 1;

            std::cout << ans << '\n';
        }
    }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

