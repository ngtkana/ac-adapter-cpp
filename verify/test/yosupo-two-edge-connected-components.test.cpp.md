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


# :heavy_check_mark: test/yosupo-two-edge-connected-components.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo-two-edge-connected-components.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-10 16:48:30+09:00


* see: <a href="https://judge.yosupo.jp/problem/two_edge_connected_components">https://judge.yosupo.jp/problem/two_edge_connected_components</a>


## Depends on

* :heavy_check_mark: <a href="../../library/graph/connectivity/tec_component.hpp.html">2-辺連結成分分解 (Two-edges components)</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"

#include <cstddef>
#include <iostream>
#include <vector>

#include "../graph/connectivity/tec_component.hpp"

int main(){
    std::size_t n, m;
    std::cin >> n >> m;
    tec_component tec(n);

    while (m--) {
        std::size_t u, v;
        std::cin >> u >> v;
        tec.insert(u, v);
    }
    tec.build();

    std::size_t sz = tec.count;
    std::vector<std::vector<std::size_t>> mem(sz);
    for (std::size_t i=0; i<n; i++) {
        mem.at(tec.cmp.at(i)).push_back(i);
    }
    std::cout << sz << '\n';
    for (auto&& v : mem) {
        std::cout << v.size();
        for (std::size_t x : v) std::cout << ' ' << x;
        std::cout << '\n';
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo-two-edge-connected-components.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"

#include <cstddef>
#include <iostream>
#include <vector>

#line 2 "graph/connectivity/tec_component.hpp"

#include <cassert>
#line 5 "graph/connectivity/tec_component.hpp"
#include <utility>
#line 7 "graph/connectivity/tec_component.hpp"
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
#line 8 "test/yosupo-two-edge-connected-components.test.cpp"

int main(){
    std::size_t n, m;
    std::cin >> n >> m;
    tec_component tec(n);

    while (m--) {
        std::size_t u, v;
        std::cin >> u >> v;
        tec.insert(u, v);
    }
    tec.build();

    std::size_t sz = tec.count;
    std::vector<std::vector<std::size_t>> mem(sz);
    for (std::size_t i=0; i<n; i++) {
        mem.at(tec.cmp.at(i)).push_back(i);
    }
    std::cout << sz << '\n';
    for (auto&& v : mem) {
        std::cout << v.size();
        for (std::size_t x : v) std::cout << ' ' << x;
        std::cout << '\n';
    }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

