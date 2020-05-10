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


# :heavy_check_mark: test/aoj-grl-1-a.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj-grl-1-a.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-10 14:26:17+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_1_A">https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_1_A</a>


## Depends on

* :heavy_check_mark: <a href="../../library/graph/edge.hpp.html">graph/edge.hpp</a>
* :heavy_check_mark: <a href="../../library/graph/shortest_path/dijkstra.hpp.html">ダイクストラ法 (Dijkstra)</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_1_A"

#include <cstddef>
#include <cassert>
#include <iostream>
#include <vector>
#include <limits>

#include "../graph/edge.hpp"
#include "../graph/shortest_path/dijkstra.hpp"

int main() {
    std::size_t n, m, s;
    std::cin >> n >> m >> s;

    std::vector<std::vector<edge<int>>> g(n);
    int inf = std::numeric_limits<int>::max();
    while (m--) {
        std::size_t u, v;
        int w;
        std::cin >> u >> v >> w;

        g.at(u).emplace_back(v, w);
    }

    std::vector<int> dist = dijkstra(g, s);

    for (int d : dist) {
        std::cout << (d==inf ? "INF" : std::to_string(d)) << '\n';
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj-grl-1-a.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_1_A"

#include <cstddef>
#include <cassert>
#include <iostream>
#include <vector>
#include <limits>

#line 2 "graph/edge.hpp"

#line 4 "graph/edge.hpp"

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
#line 2 "graph/shortest_path/dijkstra.hpp"

#include <utility>
#include <tuple>
#line 6 "graph/shortest_path/dijkstra.hpp"
#include <queue>
#line 8 "graph/shortest_path/dijkstra.hpp"

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
#line 11 "test/aoj-grl-1-a.test.cpp"

int main() {
    std::size_t n, m, s;
    std::cin >> n >> m >> s;

    std::vector<std::vector<edge<int>>> g(n);
    int inf = std::numeric_limits<int>::max();
    while (m--) {
        std::size_t u, v;
        int w;
        std::cin >> u >> v >> w;

        g.at(u).emplace_back(v, w);
    }

    std::vector<int> dist = dijkstra(g, s);

    for (int d : dist) {
        std::cout << (d==inf ? "INF" : std::to_string(d)) << '\n';
    }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

