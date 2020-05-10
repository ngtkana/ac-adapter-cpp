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


# :heavy_check_mark: test/aoj-grl-5-c.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj-grl-5-c.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-10 14:04:05+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C">https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C</a>


## Depends on

* :heavy_check_mark: <a href="../../library/graph/tree/eular_tour_lca.hpp.html">Eular tour による LCA (LCA by Eular tour)</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C"

#include "../graph/tree/eular_tour_lca.hpp"

#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>


int main() {
    std::size_t n;
    std::cin >> n;
    std::vector<std::vector<std::size_t>> g(n);

    for (std::size_t i=0; i<n; i++) {
        std::size_t k;
        std::cin >> k;

        while (k--) {
            std::size_t j;
            std::cin >> j;
            g.at(i).push_back(j);
            g.at(j).push_back(i);
        }
    }

    eular_tour_lca lca(g);

    std::size_t q;
    std::cin >> q;

    while (q--) {
        std::size_t u, v;
        std::cin >> u >> v;

        std::cout << lca.get_lca(u, v) << '\n';
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj-grl-5-c.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C"

#line 2 "graph/tree/eular_tour_lca.hpp"

#include <cstddef>
#include <cassert>
#include <utility>
#include <algorithm>
#include <vector>

struct eular_tour_lca
{
    std::vector<std::size_t> in_pos;
    std::vector<std::pair<std::size_t, std::size_t>> table;

    eular_tour_lca()=default;
    eular_tour_lca(eular_tour_lca const&)=default;
    eular_tour_lca(eular_tour_lca&&)=default;
    eular_tour_lca& operator=(eular_tour_lca const&)=default;
    eular_tour_lca& operator=(eular_tour_lca&&)=default;
    ~eular_tour_lca()=default;

    eular_tour_lca(std::vector<std::vector<std::size_t>> const& g)
        : in_pos(g.size()), table(4*g.size()-2)
    {
        std::vector<std::size_t> ord, depth(g.size());
        auto dfs = [&](auto&&f, std::size_t x, std::size_t p) -> void {
            in_pos.at(x) = ord.size();
            ord.push_back(x);
            for (std::size_t y : g.at(x)) if (y!=p) {
                depth.at(y) = depth.at(x) + 1;
                f(f, y, x);
                ord.push_back(x);
            };
        };
        dfs(dfs, 0, 0);
        assert(ord.size()==2*g.size()-1);

        for (std::size_t i=0; i<table.size()>>1; i++) {
            table.at((table.size()>>1)+i) = { depth.at(ord.at(i)), ord.at(i) };
        }
        for (std::size_t i=(table.size()>>1)-1; i; i--) {
            table.at(i) = std::min(table.at(2*i), table.at(2*i+1));
        }
    }

    std::size_t get_lca(std::size_t l, std::size_t r) const
    {
        if (l==r) return l;
        l = in_pos.at(l);
        r = in_pos.at(r);
        if (l>r) std::swap(l, r);

        std::pair<std::size_t, std::size_t> fold = {table.size(), table.size()};
        for (l+=table.size()>>1, r+=table.size()>>1; l<r; l>>=1, r>>=1)
        {
            if (l&1) fold = std::min(fold, table.at(l++));
            if (r&1) fold = std::min(fold, table.at(--r));
        }
        return fold.second;
    }
};

/*
 * @title Eular tour による LCA (LCA by Eular tour)
 * @docs tree/eular_tour_lca.md
 */
#line 4 "test/aoj-grl-5-c.test.cpp"

#line 7 "test/aoj-grl-5-c.test.cpp"
#include <iostream>
#line 9 "test/aoj-grl-5-c.test.cpp"


int main() {
    std::size_t n;
    std::cin >> n;
    std::vector<std::vector<std::size_t>> g(n);

    for (std::size_t i=0; i<n; i++) {
        std::size_t k;
        std::cin >> k;

        while (k--) {
            std::size_t j;
            std::cin >> j;
            g.at(i).push_back(j);
            g.at(j).push_back(i);
        }
    }

    eular_tour_lca lca(g);

    std::size_t q;
    std::cin >> q;

    while (q--) {
        std::size_t u, v;
        std::cin >> u >> v;

        std::cout << lca.get_lca(u, v) << '\n';
    }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

