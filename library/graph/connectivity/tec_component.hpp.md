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
    - Last commit date: 2020-05-10 16:48:30+09:00


* see: <a href="[Wikipedia k-edge-connected graph](https://en.wikipedia.org/wiki/K-edge-connected_graph)">[Wikipedia k-edge-connected graph](https://en.wikipedia.org/wiki/K-edge-connected_graph)</a>


## 仕様

`std::size_t` 型の辺を持つグラフを受け取り、2-辺連結性に関する情報を計算します。


### グラフの条件

多重辺や自己ループがあってもよいですし、非連結でもよいです。


### 構築の方法

コンストラクタに頂点数を渡します。

そのあと、`insert(i, j)` で無向辺を挿入です。

最後に `build()` で構築です。


### 情報にアクセスする方法

メンバ変数を通します。

- $ \mathtt{ bridges } $

橋のリストです。
橋 $ (u, v) $ は $ u \lt v $ を満たしますが、辞書順でソートはされていません。
これは構築の計算量オーダーを $ O ( V ) $ に抑えるためです。


- $ \mathtt{ bfree \unicode{95} graph }$

もとのグラフから橋がなくなったものです。
多重辺や自己ループもそのままのはずですが、verify はしていませんから、信頼はできません。


- $\mathtt{ count }$

2-辺連結成分の個数です。


- $ \mathtt{ cmp } $

各頂点の所属する 2-辺連結成分の番号です。

$ 0 $ から $ \mathtt{ count } - 1 $ の番号が振られています。


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
#include <algorithm>

class tec_component
{
public:
    std::vector<std::vector<std::size_t>> g;
    std::vector<std::size_t> ord, low, ckd, cmp;

    std::vector<std::vector<std::size_t>> bfree_graph;
    std::vector<std::pair<std::size_t, std::size_t>> bridges;

    std::size_t count;

private:
    void tec_internal_cmn(std::size_t& i, std::size_t j) { if (i>j) i=j; }

    void found_bridge(std::size_t i, std::size_t j) {
        if (i>j) std::swap(i, j);
        bridges.emplace_back(i, j);
    }

    void found_non_bridge(std::size_t i, std::size_t j) {
        bfree_graph.at(i).push_back(j);
        bfree_graph.at(j).push_back(i);
    }

    void dfs(std::size_t x, std::size_t p, std::size_t t) {
        auto&& v = g.at(x);
        ord.at(x) = low.at(x) = t;
        ckd.at(x) = 1;

        // 自己ループは後退辺扱いです。
        if (std::find(v.begin(), v.end(), x) != v.end()) {
            found_non_bridge(x, x);
        }

        // 親は 2 人いる場合のみ後退辺扱いです。
        if (2u <= std::count(v.begin(), v.end(), p)) {
            tec_internal_cmn(low.at(x), ord.at(p));
            found_non_bridge(x, p);
        }

        for (std::size_t y : v) {
            // 未訪問の場合です。
            if (ckd.at(y)==0u) {
                dfs(y, x, t+1);
                // 橋を見つけました。
                if (ord.at(x) < low.at(y)) {
                    found_bridge(x, y);
                // 橋でないものを見つけました。
                } else {
                    tec_internal_cmn(low.at(x), low.at(y));
                    found_non_bridge(x, y);
                }

            // 後退辺です。
            } else if (y!=p && ckd.at(y)==1u) {
                tec_internal_cmn(low.at(x), ord.at(y));
                // 後退辺は橋ではありません。
                found_non_bridge(x, y);
            }
        }
        ckd.at(x) = 2;
    }

    void efs(std::size_t x) {
        ckd.at(x) = 3u;
        for (std::size_t y : bfree_graph.at(x)) {
            if (ckd.at(y)==3u) continue;
            cmp.at(y) = cmp.at(x);
            efs(y);
        }
    }

public:
    tec_component()=default;
    tec_component(tec_component const&)=default;
    tec_component(tec_component&&)=default;
    tec_component& operator=(tec_component const&)=default;
    tec_component& operator=(tec_component&&)=default;
    ~tec_component()=default;

    tec_component(std::size_t n)
        : g(n), ord(n), low(n), ckd(n), cmp(n), bfree_graph(n), count(0)
    {}

    std::size_t size() const { return g.size(); }

    void insert(std::size_t i, std::size_t j) {
        assert(std::size_t{ 0 } <= i && i < size());
        assert(std::size_t{ 0 } <= j && j < size());
        g.at(i).push_back(j);
        g.at(j).push_back(i);
    }

    void build() {
        assert(size());

        for (std::size_t i=0; i<size(); i++) {
            dfs(i, 0, 0);
        }

        assert(std::all_of(std::begin(ckd), std::end(ckd), [](std::size_t x){ return x==2; }));

        for (std::size_t i=0; i<size(); i++) {
            if (ckd.at(i)==3u) continue;
            cmp.at(i) = count++;
            efs(i);
        }
    }
};

/*
 * @title 2-辺連結成分分解 (Two-edges components)
 * @see [Wikipedia k-edge-connected graph](https://en.wikipedia.org/wiki/K-edge-connected_graph)
 * @docs graph/connectivity/tec_component.md
 */

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
#include <algorithm>

class tec_component
{
public:
    std::vector<std::vector<std::size_t>> g;
    std::vector<std::size_t> ord, low, ckd, cmp;

    std::vector<std::vector<std::size_t>> bfree_graph;
    std::vector<std::pair<std::size_t, std::size_t>> bridges;

    std::size_t count;

private:
    void tec_internal_cmn(std::size_t& i, std::size_t j) { if (i>j) i=j; }

    void found_bridge(std::size_t i, std::size_t j) {
        if (i>j) std::swap(i, j);
        bridges.emplace_back(i, j);
    }

    void found_non_bridge(std::size_t i, std::size_t j) {
        bfree_graph.at(i).push_back(j);
        bfree_graph.at(j).push_back(i);
    }

    void dfs(std::size_t x, std::size_t p, std::size_t t) {
        auto&& v = g.at(x);
        ord.at(x) = low.at(x) = t;
        ckd.at(x) = 1;

        // 自己ループは後退辺扱いです。
        if (std::find(v.begin(), v.end(), x) != v.end()) {
            found_non_bridge(x, x);
        }

        // 親は 2 人いる場合のみ後退辺扱いです。
        if (2u <= std::count(v.begin(), v.end(), p)) {
            tec_internal_cmn(low.at(x), ord.at(p));
            found_non_bridge(x, p);
        }

        for (std::size_t y : v) {
            // 未訪問の場合です。
            if (ckd.at(y)==0u) {
                dfs(y, x, t+1);
                // 橋を見つけました。
                if (ord.at(x) < low.at(y)) {
                    found_bridge(x, y);
                // 橋でないものを見つけました。
                } else {
                    tec_internal_cmn(low.at(x), low.at(y));
                    found_non_bridge(x, y);
                }

            // 後退辺です。
            } else if (y!=p && ckd.at(y)==1u) {
                tec_internal_cmn(low.at(x), ord.at(y));
                // 後退辺は橋ではありません。
                found_non_bridge(x, y);
            }
        }
        ckd.at(x) = 2;
    }

    void efs(std::size_t x) {
        ckd.at(x) = 3u;
        for (std::size_t y : bfree_graph.at(x)) {
            if (ckd.at(y)==3u) continue;
            cmp.at(y) = cmp.at(x);
            efs(y);
        }
    }

public:
    tec_component()=default;
    tec_component(tec_component const&)=default;
    tec_component(tec_component&&)=default;
    tec_component& operator=(tec_component const&)=default;
    tec_component& operator=(tec_component&&)=default;
    ~tec_component()=default;

    tec_component(std::size_t n)
        : g(n), ord(n), low(n), ckd(n), cmp(n), bfree_graph(n), count(0)
    {}

    std::size_t size() const { return g.size(); }

    void insert(std::size_t i, std::size_t j) {
        assert(std::size_t{ 0 } <= i && i < size());
        assert(std::size_t{ 0 } <= j && j < size());
        g.at(i).push_back(j);
        g.at(j).push_back(i);
    }

    void build() {
        assert(size());

        for (std::size_t i=0; i<size(); i++) {
            dfs(i, 0, 0);
        }

        assert(std::all_of(std::begin(ckd), std::end(ckd), [](std::size_t x){ return x==2; }));

        for (std::size_t i=0; i<size(); i++) {
            if (ckd.at(i)==3u) continue;
            cmp.at(i) = count++;
            efs(i);
        }
    }
};

/*
 * @title 2-辺連結成分分解 (Two-edges components)
 * @see [Wikipedia k-edge-connected graph](https://en.wikipedia.org/wiki/K-edge-connected_graph)
 * @docs graph/connectivity/tec_component.md
 */

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

