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


# :heavy_check_mark: セグメント木 (segtree)

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#eae30ef778b4136fdcc54087b7400598">segtree</a>
* <a href="{{ site.github.repository_url }}/blob/master/segtree/segtree.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-11 23:59:36+09:00




## 構築

- $ \mathtt{ segtree(n, init=Monoid::id()) } $: サイズと初期値を指定です。

- $ \mathtt{ lazy \unicode{95} set( i, x ) } $: 葉に値をセットしますが、構築をしません。

- $ \mathtt{ build } $: 構築をします。

- $ \mathtt{ resize(n, init=Monoid::id()) } $: サイズと初期値を指定です。$ \mathtt { segtree } $を$ vector $に入れたいときなど、デフォルト構築をはさみたい場面で使います。


## オブザーバー

- $ \mathtt{ size() } $: 構築で指定したサイズです。

- $ \mathtt{ fold(l, r) } $: 開区間$ [ l, r [ $で畳み込みをします。

- $ \mathtt{ get(i) }$: 添字$ i $にある値を取得です。

- $ \mathtt{ to \unicode{95} vec() }$: $ \mathtt{ vector } $ に値をコレクトします。


## 更新

- $ \mathtt{ set(i, x) } $: 添字$ i $の値を$ x $に変更します。

- $ \mathtt{ add(i, x) } $: 添字$ i $の値を$ \mathtt{ get (i) + x } $に変更します。

- $ \mathtt{ sub(i, x) } $: 添字$ i $の値を$ \mathtt{ get (i) - x } $に変更します。

- $ \mathtt{ mul(i, x) } $: 添字$ i $の値を$ \mathtt{ get (i) * x } $に変更します。

- $ \mathtt{ div(i, x) } $: 添字$ i $の値を$ \mathtt{ get (i) / x } $に変更します。

- $ \mathtt{ map(i, f) } $: 添字$ i $の値を$ \mathtt{ f( get (i) ) } $に変更します。



## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj-dsl-2-a.test.cpp.html">test/aoj-dsl-2-a.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj-dsl-2-b.test.cpp.html">test/aoj-dsl-2-b.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 349, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=pathlib.Path.cwd())
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 185, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 239, in update
    raise BundleErrorAt(path, i + 1, "#pragma once found in a non-first line")
onlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: segtree/segtree.hpp: line 6: #pragma once found in a non-first line

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

