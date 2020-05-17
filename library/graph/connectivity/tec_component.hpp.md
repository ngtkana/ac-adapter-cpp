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


# :heavy_check_mark: 2-辺連結成分分解 (Two-edges components)

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#419122d444c505324448ed1b2f731265">graph/connectivity</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/connectivity/tec_component.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-17 16:07:39+09:00


* see: <a href="[Wikipedia k-edge-connected graph](https://en.wikipedia.org/wiki/K-edge-connected_graph)">[Wikipedia k-edge-connected graph](https://en.wikipedia.org/wiki/K-edge-connected_graph)</a>


# 概要

$ \mathtt { usize } $ 型の辺を持つグラフを受け取り、2-辺連結性に関する情報を計算します。

多重辺や自己ループがあってもよいですし、非連結でもよいです。


# 仕様

## 構築

### 構築方法1: あとで挿入

- $ \mathtt { tec \unicode { 95 } component ( n ) } $: サイズ $ n $ です。

- $ \mathtt { insert ( u, v ) } $: 無向辺を挿入です。

### 構築方法2: グラフどーん

- $ \mathtt { tec \unicode { 95 } component ( g ) } $: どーん


最後に `build()` で構築です。


## 計算結果の取得

### メンバ変数

$ \mathtt { build () } $ をしてから、メンバ変数にアクセスです。

- $ \mathtt{ bridges } $: 橋のリストです。
橋 $ (u, v) $ は $ u \lt v $ を満たしますが、辞書順でソートはされていません。
これは構築の計算量オーダーを $ O ( V ) $ に抑えるためです。

- $\mathtt{ count }$: 2-辺連結成分の個数です。


- $ \mathtt{ cmp } $: 各頂点の所属する 2-辺連結成分の番号です。
$ 0 $ から $ \mathtt{ count } - 1 $ の番号が振られています。


### メンバ関数

商グラフだけは、メンバ関数で取得です。
こちらは、未構築な場合は自動で $ \mathtt { build() } $ が呼ばれます。
ほかのメンバ変数もそのような感じにしたほうがよいでしょうか。
（こういうときに C# が羨ましくなります。）（ムーブ代入演算子オーバーロード（ボソッ））

- $ \mathtt { quotient \unicode { 95 } graph } $: 商グラフを構築です。


## Depends on

* :heavy_check_mark: <a href="../../others/cstdint2.hpp.html">others/cstdint2.hpp</a>
* :heavy_check_mark: <a href="../../others/vec.hpp.html">others/vec.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj-grl-3-b.test.cpp.html">test/aoj-grl-3-b.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/yosupo-two-edge-connected-components.test.cpp.html">test/yosupo-two-edge-connected-components.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>
#include <tuple>
#include <algorithm>

#include "../../others/cstdint2.hpp"
#include "../../others/vec.hpp"

/*
 * @title 2-辺連結成分分解 (Two-edges components)
 * @see [Wikipedia k-edge-connected graph](https://en.wikipedia.org/wiki/K-edge-connected_graph)
 * @docs graph/connectivity/tec_component.md
 */

class tec_component {
    bool built;

    // 1 回目の DFS
    // 計算するもの: ord, low, bridges
    // precondition: ckd = 0
    // post-condition: ckd = 2
    void low_link_dfs(usize x, usize p, usize& t) {
        auto&& v = g.at(x);
        ord.at(x) = low.at(x) = t++;
        ckd.at(x) = 1;

        // 親への多重辺
        if (2u <= std::count(v.begin(), v.end(), p)) {
            if (low.at(x) > ord.at(p)) low.at(x) = ord.at(p);
        }

        for (usize y : v) {
            // 未訪問の場合です。
            if (ckd.at(y)==0u) {
                low_link_dfs(y, x, t);
                // 橋を見つけました。
                if (ord.at(x) < low.at(y)) {
                    bridges.emplace_back(std::min(x, y), std::max(x, y));
                } else {
                    if (low.at(x) > low.at(y)) low.at(x) = low.at(y);
                }
            // 後退辺です。
            } else if (y!=p && ckd.at(y)==1u) {
                if (low.at(x) > ord.at(y)) low.at(x) = ord.at(y);
            }
        }
        ckd.at(x) = 2;
    }

    // 2 回目の DFS
    // 計算するも: cmp
    // precondition: cmp = size()
    // post-condition: cmp が計算済み
    void cmp_dfs(usize x) {
        for (usize y : g.at(x)) if (cmp.at(y)==size()) {
            cmp.at(y) = ord.at(x)<low.at(y)? ++count : cmp.at(x);
            cmp_dfs(y);
        }
    }

public:
    vec<vec<usize>> g;
    vec<usize> ord, low, ckd, cmp;

    vec<std::pair<usize, usize>> bridges;

    usize count;

    tec_component()=default;
    tec_component(tec_component const&)=default;
    tec_component(tec_component&&)=default;
    tec_component& operator=(tec_component const&)=default;
    tec_component& operator=(tec_component&&)=default;
    ~tec_component()=default;

    tec_component(vec<vec<usize>> const& g_)
        : tec_component(g_.size())
    {
        g = g_;
    }

    tec_component(usize n)
        : built(false), g(n), ord(n), low(n), ckd(n), cmp(n, n), count(0)
    {}

    void insert(usize i, usize j) {
        assert(usize{ 0 } <= i && i < size());
        assert(usize{ 0 } <= j && j < size());
        g.at(i).push_back(j);
        g.at(j).push_back(i);
    }


    usize size() const { return g.size(); }

    void build() {
        assert(built == false);
        built = true;

        for (usize i=0, t=0; i<size(); i++) if (ckd.at(i)==0) {
            low_link_dfs(i, 0, t);
        }

        assert(std::all_of(std::begin(ckd), std::end(ckd), [](usize x){ return x==2; }));

        for (usize i=0; i<size(); i++) if (cmp.at(i)==size()) {
            cmp.at(i) = count;
            cmp_dfs(i);
            count++;
        }
    }

    vec<vec<usize>> quotient_graph() {
        if (!built) build();
        vec<vec<usize>> h(count);

        for (auto&& e: bridges) {
            usize u, v;
            std::tie(u, v) = e;
            u = cmp.at(u);
            v = cmp.at(v);

            h.at(u).push_back(v);
            h.at(v).push_back(u);
        }
        return h;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph/connectivity/tec_component.hpp"

#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>
#include <tuple>
#include <algorithm>

#line 2 "others/cstdint2.hpp"

#include <cstdint>

using i32 = std::int_least32_t;
using i64 = std::int_least64_t;
using u32 = std::uint_least32_t;
using u64 = std::uint_least64_t;
using usize = std::size_t;
#line 1 "others/vec.hpp"
template <class T> using vec = std::vector<T>;
#line 12 "graph/connectivity/tec_component.hpp"

/*
 * @title 2-辺連結成分分解 (Two-edges components)
 * @see [Wikipedia k-edge-connected graph](https://en.wikipedia.org/wiki/K-edge-connected_graph)
 * @docs graph/connectivity/tec_component.md
 */

class tec_component {
    bool built;

    // 1 回目の DFS
    // 計算するもの: ord, low, bridges
    // precondition: ckd = 0
    // post-condition: ckd = 2
    void low_link_dfs(usize x, usize p, usize& t) {
        auto&& v = g.at(x);
        ord.at(x) = low.at(x) = t++;
        ckd.at(x) = 1;

        // 親への多重辺
        if (2u <= std::count(v.begin(), v.end(), p)) {
            if (low.at(x) > ord.at(p)) low.at(x) = ord.at(p);
        }

        for (usize y : v) {
            // 未訪問の場合です。
            if (ckd.at(y)==0u) {
                low_link_dfs(y, x, t);
                // 橋を見つけました。
                if (ord.at(x) < low.at(y)) {
                    bridges.emplace_back(std::min(x, y), std::max(x, y));
                } else {
                    if (low.at(x) > low.at(y)) low.at(x) = low.at(y);
                }
            // 後退辺です。
            } else if (y!=p && ckd.at(y)==1u) {
                if (low.at(x) > ord.at(y)) low.at(x) = ord.at(y);
            }
        }
        ckd.at(x) = 2;
    }

    // 2 回目の DFS
    // 計算するも: cmp
    // precondition: cmp = size()
    // post-condition: cmp が計算済み
    void cmp_dfs(usize x) {
        for (usize y : g.at(x)) if (cmp.at(y)==size()) {
            cmp.at(y) = ord.at(x)<low.at(y)? ++count : cmp.at(x);
            cmp_dfs(y);
        }
    }

public:
    vec<vec<usize>> g;
    vec<usize> ord, low, ckd, cmp;

    vec<std::pair<usize, usize>> bridges;

    usize count;

    tec_component()=default;
    tec_component(tec_component const&)=default;
    tec_component(tec_component&&)=default;
    tec_component& operator=(tec_component const&)=default;
    tec_component& operator=(tec_component&&)=default;
    ~tec_component()=default;

    tec_component(vec<vec<usize>> const& g_)
        : tec_component(g_.size())
    {
        g = g_;
    }

    tec_component(usize n)
        : built(false), g(n), ord(n), low(n), ckd(n), cmp(n, n), count(0)
    {}

    void insert(usize i, usize j) {
        assert(usize{ 0 } <= i && i < size());
        assert(usize{ 0 } <= j && j < size());
        g.at(i).push_back(j);
        g.at(j).push_back(i);
    }


    usize size() const { return g.size(); }

    void build() {
        assert(built == false);
        built = true;

        for (usize i=0, t=0; i<size(); i++) if (ckd.at(i)==0) {
            low_link_dfs(i, 0, t);
        }

        assert(std::all_of(std::begin(ckd), std::end(ckd), [](usize x){ return x==2; }));

        for (usize i=0; i<size(); i++) if (cmp.at(i)==size()) {
            cmp.at(i) = count;
            cmp_dfs(i);
            count++;
        }
    }

    vec<vec<usize>> quotient_graph() {
        if (!built) build();
        vec<vec<usize>> h(count);

        for (auto&& e: bridges) {
            usize u, v;
            std::tie(u, v) = e;
            u = cmp.at(u);
            v = cmp.at(v);

            h.at(u).push_back(v);
            h.at(v).push_back(u);
        }
        return h;
    }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

