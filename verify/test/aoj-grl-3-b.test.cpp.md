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


# :heavy_check_mark: test/aoj-grl-3-b.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj-grl-3-b.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-22 00:36:51+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_3_B">https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_3_B</a>


## Depends on

* :heavy_check_mark: <a href="../../library/graph/connectivity/tec_component.hpp.html">2-辺連結成分分解 (Two-edges components)</a>
* :heavy_check_mark: <a href="../../library/others/cstdint2.hpp.html">others/cstdint2.hpp</a>
* :heavy_check_mark: <a href="../../library/others/vec.hpp.html">others/vec.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_3_B"

#include <cstddef>
#include <iostream>
#include <utility>
#include <tuple>
#include <vector>
#include <algorithm>

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

    std::vector<std::pair<std::size_t, std::size_t>> bridges = tec.bridges;
    std::sort(bridges.begin(), bridges.end());

    for (auto&& e : bridges) {
        std::size_t i, j;
        std::tie(i, j) = e;
        std::cout << i << ' ' << j << '\n';
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj-grl-3-b.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_3_B"

#include <cstddef>
#include <iostream>
#include <utility>
#include <tuple>
#include <vector>
#include <algorithm>

#line 2 "graph/connectivity/tec_component.hpp"

#include <cassert>
#line 9 "graph/connectivity/tec_component.hpp"

#line 2 "others/cstdint2.hpp"

#include <cstdint>

using i32 = std::int_least32_t;
using i64 = std::int_least64_t;
using u32 = std::uint_least32_t;
using u64 = std::uint_least64_t;
using usize = std::size_t;
#line 1 "others/vec.hpp"



#line 5 "others/vec.hpp"

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
#line 11 "test/aoj-grl-3-b.test.cpp"

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

    std::vector<std::pair<std::size_t, std::size_t>> bridges = tec.bridges;
    std::sort(bridges.begin(), bridges.end());

    for (auto&& e : bridges) {
        std::size_t i, j;
        std::tie(i, j) = e;
        std::cout << i << ' ' << j << '\n';
    }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

