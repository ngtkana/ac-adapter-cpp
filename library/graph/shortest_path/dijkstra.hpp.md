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


# :heavy_check_mark: ダイクストラ法 (Dijkstra)

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#fff28642b706f0621a80a098b694618d">graph/shortest_path</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/shortest_path/dijkstra.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-10 14:26:17+09:00




## 仕様

`edge<Weight>` 型の辺を持つグラフを受け取ります。
この型は、メンバ変数 `to`, `weight` を持つことが要求されます。
到達不能な場合は、`std::numeric_limits<Weight>` で埋められます。


## 悩みごと

こちらも edge adapter のようなものを受け取るほうがキレイかもしれません。
また、最短路問題のために、「無限大」メンバ関数を持つ edge adapter を使うと良いかもしれません。

これを先送りにしている理由はふたつです。
ひとつにはこのようなアダプターは、作るならばいくつも必要ですし、また何が必要かも今の所あまりよく分かっていないからです。
もうひとつには、ユーザーコードに迷惑を書けない自信がまだないからです。




## Depends on

* :heavy_check_mark: <a href="../edge.hpp.html">graph/edge.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj-grl-1-a.test.cpp.html">test/aoj-grl-1-a.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <utility>
#include <tuple>
#include <vector>
#include <queue>
#include <limits>

#include "../edge.hpp"

template <class Weight> std::vector<Weight>
dijkstra(std::vector<std::vector<edge<Weight>>> const& g, std::size_t s)
{
    assert(0 <= s && s < g.size());
    Weight inf = std::numeric_limits<Weight>::max();
    std::vector<Weight> dist(g.size(), inf);
    std::priority_queue<std::pair<Weight, std::size_t>> que;

    dist.at(s) = 0;
    que.emplace(0, s);
    while (!que.empty()) {
        std::size_t x;
        Weight dx;
        std::tie(dx, x) = que.top(); que.pop();
        dx = -dx;

        if (dist.at(x) < dx) continue;

        for (auto&& e : g.at(x)) {
            std::size_t y = e.to;
            Weight dy = dx + e.weight;

            if (dist.at(y) <= dy) continue;
            dist.at(y) = dy;
            que.emplace(-dy, y);
        }
    }

    return dist;
}

/*
 * @title ダイクストラ法 (Dijkstra)
 * @docs graph/shortest_path/dijkstra.md
 */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph/shortest_path/dijkstra.hpp"

#include <utility>
#include <tuple>
#include <vector>
#include <queue>
#include <limits>

#line 2 "graph/edge.hpp"

#include <iostream>

template <class Weight>
struct edge {
    std::size_t to;
    Weight weight;

    edge()=default;
    edge(edge const&)=default;
    edge(edge&&)=default;
    edge& operator=(edge const&)=default;
    edge& operator=(edge&&)=default;
    ~edge()=default;

    edge(std::size_t to_, Weight weight_)
        : to(to_), weight(weight_) {}
};

template <class Weight> std::ostream&
operator<< (std::ostream& os, edge<Weight> e)
{
    return os << '(' << e.to << ',' << e.weight << ')';
}
#line 10 "graph/shortest_path/dijkstra.hpp"

template <class Weight> std::vector<Weight>
dijkstra(std::vector<std::vector<edge<Weight>>> const& g, std::size_t s)
{
    assert(0 <= s && s < g.size());
    Weight inf = std::numeric_limits<Weight>::max();
    std::vector<Weight> dist(g.size(), inf);
    std::priority_queue<std::pair<Weight, std::size_t>> que;

    dist.at(s) = 0;
    que.emplace(0, s);
    while (!que.empty()) {
        std::size_t x;
        Weight dx;
        std::tie(dx, x) = que.top(); que.pop();
        dx = -dx;

        if (dist.at(x) < dx) continue;

        for (auto&& e : g.at(x)) {
            std::size_t y = e.to;
            Weight dy = dx + e.weight;

            if (dist.at(y) <= dy) continue;
            dist.at(y) = dy;
            que.emplace(-dy, y);
        }
    }

    return dist;
}

/*
 * @title ダイクストラ法 (Dijkstra)
 * @docs graph/shortest_path/dijkstra.md
 */

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

