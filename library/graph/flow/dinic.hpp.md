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


# :heavy_check_mark: Dinic

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#cff5497121104c2b8e0cb41ed2083a9b">flow</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/flow/dinic.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-03 15:19:38+09:00


* see: <a href="https://en.wikipedia.org/wiki/Dinic%27s_algorithm">https://en.wikipedia.org/wiki/Dinic%27s_algorithm</a>


## Depends on

* :heavy_check_mark: <a href="flow_edge.hpp.html">graph/flow/flow_edge.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj-grl-6-a-1.test.cpp.html">test/aoj-grl-6-a-1.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "flow_edge.hpp"

#include <vector>
#include <cstddef>
#include <algorithm>

template <class Flow> class dinic {
    std::size_t s, t;
    int time;
    std::vector<std::vector<flow_edge<Flow>>> g;
    std::vector<int> ckd, dist;

    // 距離を計算します。
    void init_dist() {
        dist.assign(size(), -1);
        dist.at(s) = 0;
        std::vector<std::size_t> que = {s};

        for (std::size_t i=0; i<que.size(); i++) {
            std::size_t x=que.at(i);

            for (auto&& e : g.at(x)) if (dist.at(e.to)==-1 && e.cap!=zero()) {
                dist.at(e.to) = dist.at(x) + 1;
                que.push_back(e.to);
            }
        }
    }

    // 増分路を探します。
    Flow find_aug(std::size_t x, Flow d /* フローが来ました */) {
        ckd.at(x) = time;
        if (x == t) return d;

        for (auto&& e : g.at(x)) if (ckd.at(e.to)!=time && e.cap!=zero()) {
            Flow ret = find_aug(e.to, std::min(d, e.cap) /* 次に送ります */); // 帰ってきました
            if (ret==zero())continue;

            e.cap -= ret;
            g.at(e.to).at(e.rev).cap += ret;
            return ret; // さらに返します
        }
        return zero();
    }

public:
    // special member functions
    dinic()=default;
    dinic(const dinic&)=default;
    dinic(dinic&&)=default;
    dinic&operator=(const dinic&)=default;
    dinic&operator=(dinic&&)=default;
    ~dinic()=default;

    dinic(std::size_t n, std::size_t s_, int t_)
        : s(s_), t(t_), time(0), g(n), ckd(n, -1) {}

    std::size_t size() const noexcept { return g.size(); }

    Flow inf() const { return std::numeric_limits<Flow>::max(); }

    Flow zero() const { return Flow{ 0 }; }

    void insert(std::size_t u, std::size_t v, Flow w) {
        std::size_t su = g.at(u).size();
        std::size_t sv = g.at(v).size();

        g.at(u).emplace_back(v, sv, w);
        g.at(v).emplace_back(u, su, zero());
    }

    Flow run() {
        Flow flow = zero();

        for(Flow f; ; time++) {
            f = find_aug(s, inf());
            if (f == zero()) break;
            if (f == inf()) return inf(); // 容量無限の辺があるケースに対応です。
            flow += f;
        }

        return flow;
    }
};

/*
 * 
 * @title Dinic
 * @category graph
 * @category flow
 * @brief 計算量は $ O ( V^2 E ) $ です。
 * @see https://en.wikipedia.org/wiki/Dinic%27s_algorithm
 */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph/flow/dinic.hpp"

#line 2 "graph/flow/flow_edge.hpp"

#include <iostream>
#include <cstddef>

template <class Flow> struct flow_edge {
    std::size_t to;
    std::size_t rev;
    Flow cap;

    // special member functions
    flow_edge()=default;
    flow_edge(const flow_edge&)=default;
    flow_edge(flow_edge&&)=default;
    flow_edge&operator=(const flow_edge&)=default;
    flow_edge&operator=(flow_edge&&)=default;
    ~flow_edge()=default;

    flow_edge(std::size_t to_, std::size_t rev_, Flow cap_)
        : to(to_), rev(rev_), cap(cap_) {}
};

template <class Flow> std::ostream& operator<<(std::ostream& os, flow_edge<Flow> e) {
    return os << "(" << e.to << "," << e.cap << ")";
}
#line 4 "graph/flow/dinic.hpp"

#include <vector>
#line 7 "graph/flow/dinic.hpp"
#include <algorithm>

template <class Flow> class dinic {
    std::size_t s, t;
    int time;
    std::vector<std::vector<flow_edge<Flow>>> g;
    std::vector<int> ckd, dist;

    // 距離を計算します。
    void init_dist() {
        dist.assign(size(), -1);
        dist.at(s) = 0;
        std::vector<std::size_t> que = {s};

        for (std::size_t i=0; i<que.size(); i++) {
            std::size_t x=que.at(i);

            for (auto&& e : g.at(x)) if (dist.at(e.to)==-1 && e.cap!=zero()) {
                dist.at(e.to) = dist.at(x) + 1;
                que.push_back(e.to);
            }
        }
    }

    // 増分路を探します。
    Flow find_aug(std::size_t x, Flow d /* フローが来ました */) {
        ckd.at(x) = time;
        if (x == t) return d;

        for (auto&& e : g.at(x)) if (ckd.at(e.to)!=time && e.cap!=zero()) {
            Flow ret = find_aug(e.to, std::min(d, e.cap) /* 次に送ります */); // 帰ってきました
            if (ret==zero())continue;

            e.cap -= ret;
            g.at(e.to).at(e.rev).cap += ret;
            return ret; // さらに返します
        }
        return zero();
    }

public:
    // special member functions
    dinic()=default;
    dinic(const dinic&)=default;
    dinic(dinic&&)=default;
    dinic&operator=(const dinic&)=default;
    dinic&operator=(dinic&&)=default;
    ~dinic()=default;

    dinic(std::size_t n, std::size_t s_, int t_)
        : s(s_), t(t_), time(0), g(n), ckd(n, -1) {}

    std::size_t size() const noexcept { return g.size(); }

    Flow inf() const { return std::numeric_limits<Flow>::max(); }

    Flow zero() const { return Flow{ 0 }; }

    void insert(std::size_t u, std::size_t v, Flow w) {
        std::size_t su = g.at(u).size();
        std::size_t sv = g.at(v).size();

        g.at(u).emplace_back(v, sv, w);
        g.at(v).emplace_back(u, su, zero());
    }

    Flow run() {
        Flow flow = zero();

        for(Flow f; ; time++) {
            f = find_aug(s, inf());
            if (f == zero()) break;
            if (f == inf()) return inf(); // 容量無限の辺があるケースに対応です。
            flow += f;
        }

        return flow;
    }
};

/*
 * 
 * @title Dinic
 * @category graph
 * @category flow
 * @brief 計算量は $ O ( V^2 E ) $ です。
 * @see https://en.wikipedia.org/wiki/Dinic%27s_algorithm
 */

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

