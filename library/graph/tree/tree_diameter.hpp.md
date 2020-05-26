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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: 木の直径 (Diameer of tree)

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#28790b6202284cbbffc9d712b59f4b80">graph/tree</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/tree/tree_diameter.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-23 02:06:19+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_A">https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_A</a>


# 概略

重み付き、乃至重みなしな木の直径を計算します。また、特に指定すると直径を達成するパスをひとつ取得することができます。

$ \mathtt { tree \unicode { 95 } diameter \<\> } $ は重みなし（辺は $ \mathtt { usize } $ ）のグラフを、
$ \mathtt { tree \unicode { 95 } diameter \<i64\> } $ は $ \mathtt { i64 } $ 型の重みを持つ（辺は $ \mathtt { pair\<usize, Weight\> } $ ) グラフを管理します。

なお、頂点数が 0 のときには実行時エラーになります。


## 型の紹介です。

- $ \mathtt { tree \unicode { 95 } diameter \<Weight\> }$: 本体です。

- $ \mathtt { no \unicode { 95 } weight } $: ユーザーが知らなくても良い型です。上記の分岐のための空構造体です。

- $ \mathtt { tree \unicode { 95 } diameter \unicode { 95 } adapter\<Weight\> } $: ユーザーが知らなくても良い型です。
辺から $ \mathtt { to } $ や $ \mathtt { weight } $ などを取る方法を知っています。
$ \mathtt { tree \unicode { 95 } diameter \<Weight\> } $ の中で使われます。


# 仕様

## 構築

### 構築方法 1: サイズを指定して、あとから $ \mathtt { insert } $ です。

- $ \mathtt { tree \unicode { 95 } diameter ( n ) } $: 頂点数 $ n $ です。グラフはまだからです。

- $ \mathtt { insert \unicode { 95 } with \unicode { 95 } weight (u, v) }$:
頂点 $ u $ と $ v $ を辺で結びます。
$ \mathtt { Weight } $ が $ \mathtt { no \unicode { 95 } weight } $ でないときに実体化するとコンパイルエラーになります。

- $ \mathtt { insert \unicode { 95 } without \unicode { 95 } weight (u, v, w) }$:
頂点 $ u $ と $ v $ を重み $ w $ の辺で結びます。
$ \mathtt { Weight } $ が $ \mathtt { no \unicode { 95 } weight } $ であるときに実体化するとコンパイルエラーになります。

TODO: 重み有りとなしで、そぐわない方のメンバ関数が、そもそも生えないようにメタプロをしても良いかもしれません。（とはいえお名前が違うほうが良いという説もです。）


### 構築方法 2: グラフを渡します。

- $ \mathtt { tree \unicode { 95 } diameter ( g ) } $: グラフを受け取ります。


## 計算

### 方法 1: 全体です。

- $ \mathtt{ build(s=0) }$: <var> s </var> からはじめます。


### 方法 2: 全体です。

- $ \mathtt{ build(s, dead) }$: 始点と頂点の死リストを受け取ります。<var> s </var> が死んでいる場合は実行時エラーです。

TODO: 実装を共通化しても良いかもしれません。


## 計算結果の取得

$ \mathtt { build () } $ を呼ぶと直径の両端点と、距離配列が初期化されます。
これを 2 回以上行うと実行時エラーです。

以下に列挙するメンバ関数は、すべて $ \mathtt { build () } $ が済んでいる前提です。

- $ \mathtt { len() } $: 直径の長さ（間の辺の重みの合計）を返します。

- $ \mathtt { extremals () } $: 直径の両端点を $ \mathtt{ s, t } $ の順で $ \mathtt { pair } $ で返します。

- $ \mathtt { verticies() } $: 直径に属する頂点の列を $ \mathtt { vec } $ で返します。重みなしの場合、この $ \mathtt { vec } $ の長さは $ \mathtt { len() } + 1 $ に一致します。

- $ \mathtt { dist } $: 使うかわからないのですが、$ t $ からの距離の情報の入ったメンバ変数です。


## Depends on

* :heavy_check_mark: <a href="../../others/cstdint2.hpp.html">others/cstdint2.hpp</a>
* :heavy_check_mark: <a href="../../others/vec.hpp.html">others/vec.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj-grl-5-a.test.cpp.html">test/aoj-grl-5-a.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/*
 * @title 木の直径 (Diameer of tree)
 * @docs graph/tree/tree_diameter.md
 */

#pragma once

#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_A"

#include <cassert>
#include <cstddef>
#include <utility>
#include <algorithm>
#include <vector>
#include <limits>

#include "../../others/cstdint2.hpp"
#include "../../others/vec.hpp"

struct no_weight;

template <class Weight>
struct tree_diameter_adapter {
    using weight_type = Weight;
    using edge_type = std::pair<usize, weight_type>;
    static usize to(edge_type const& e) { return e.first; }
    static weight_type weight(edge_type const& e) { return e.second; }
};

template <>
struct tree_diameter_adapter<no_weight> {
    using weight_type = usize;
    using edge_type = usize;
    static usize to(edge_type e) { return e; }
    static weight_type weight(edge_type) { return 1; }
};

template <class> class tree_diameter;

template <class Weight=no_weight>
class tree_diameter {
    using adapter_type = tree_diameter_adapter<Weight>;
    using edge_type = typename adapter_type::edge_type;
    using weight_type = typename adapter_type::weight_type;
    using this_type = tree_diameter<Weight>;

    bool built = false;

    static weight_type inf() { return std::numeric_limits<weight_type>::max(); }

public:
    vec<vec<edge_type>> g;
    vec<weight_type> dist;
    usize s, t;

    tree_diameter()=default;
    tree_diameter(tree_diameter const&)=default;
    tree_diameter(tree_diameter&&)=default;
    tree_diameter& operator=(tree_diameter const&)=default;
    tree_diameter& operator=(tree_diameter&&)=default;
    ~tree_diameter()=default;

    tree_diameter(usize n)
        : g(n), dist(n) {}

    void insert_with_weight(usize u, usize v, Weight w) {
        assert(u < size());
        assert(v < size());
        g.at(u).emplace_back(v, w);
        g.at(v).emplace_back(u, w);
    }

    void insert_without_weight(usize u, usize v) {
        assert(u < size());
        assert(v < size());
        g.at(u).push_back(v);
        g.at(v).push_back(u);
    }

    tree_diameter(vec<vec<edge_type>> const& g_)
        : g(g_), dist(g_.size())
    {}

    usize size() const { return g.size(); }

    this_type& build(usize s_ = 0) {
        assert(!built);
        built = true;
        s = s_;

        for (usize i=0; i<2; i++) {
            dist.assign(size(), inf());
            dist.at(s) = 0;
            vec<usize> que = {s};

            for (usize j=0; j<que.size(); j++) {
                usize x = que.at(j);
                for (auto&& e: g.at(x)) if (dist.at(adapter_type::to(e))==inf()) {
                    dist.at(adapter_type::to(e)) = dist.at(x) + adapter_type::weight(e);
                    que.push_back(adapter_type::to(e));
                }
            }
            t = std::max_element(dist.begin(), dist.end()) - dist.begin();
            std::swap(s, t);
        }
        return *this;
    }

    // これちょっと雑かもです。
    this_type& build(usize s_, vec<usize> const& dead) {
        assert(!built);
        assert(dead.size()==size());
        assert(!dead.at(s_));
        built = true;
        s = s_;

        for (usize i=0; i<2; i++) {
            dist.assign(size(), inf());
            dist.at(s) = 0;
            vec<usize> que = {s};

            for (usize j=0; j<que.size(); j++) {
                usize x = que.at(j);
                for (auto&& e: g.at(x)) if (dist.at(adapter_type::to(e))==inf() && !dead.at(adapter_type::to(e))) {
                    dist.at(adapter_type::to(e)) = dist.at(x) + adapter_type::weight(e);
                    que.push_back(adapter_type::to(e));
                }
            }
            t = s;
            for (usize j=0; j<size(); j++) if (dist.at(j)!=inf()) {
                if (dist.at(t) < dist.at(j)) t = j;
            }
            std::swap(s, t);
        }
        return *this;
    }

    weight_type len() const {
        assert(built);
        assert(dist.at(t)==0 && dist.at(s)!=inf());
        return dist.at(s);
    }

    std::pair<usize, usize> extremals() const {
        assert(built);
        assert(dist.at(t)==0 && dist.at(s)!=inf());
        return std::make_pair(s, t);
    }

    vec<usize> verticies() const {
        assert(built);
         vec<usize> ans = {s};
         while (ans.back()!=t) {
             auto&& v = g.at(ans.back());

             usize y =
                 adapter_type::to(*std::find_if(
                     v.begin(),
                     v.end(),
                     [this, dx=dist.at(ans.back())](usize y_){
                         return dist.at(y_) == dx - 1;
                     }
                 ));

             ans.push_back(y);
         }
         assert(ans.size()==len()+1);
         assert([&]{
             for (usize i=0; i<=len(); i++) {
                 assert(i==len()-dist.at(ans.at(i)));
             }
             return true;
         }());
         return ans;
    }
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
onlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/tree/tree_diameter.hpp: line 6: #pragma once found in a non-first line

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

