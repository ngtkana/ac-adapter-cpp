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


# :heavy_check_mark: test/aoj-grl-6-a.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj-grl-6-a.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-03 15:19:31+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A">https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A</a>


## Depends on

* :heavy_check_mark: <a href="../../library/graph/flow/flow_edge.hpp.html">graph/flow/flow_edge.hpp</a>
* :heavy_check_mark: <a href="../../library/graph/flow/ford_fulkerson.hpp.html">Ford−Fulkerson</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A"

#include "../graph/flow/ford_fulkerson.hpp"

#include <iostream>

int main(){
    int n, m;
    std::cin >> n >> m;

    auto ff=ford_fulkerson<int>(n, 0, n-1);

    while(m--){
        int u, v, c;
        std::cin >> u >> v >> c;

        ff.insert(u, v, c);
    }

    std::cout<<ff.run()<<'\n';
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj-grl-6-a.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A"

#line 2 "graph/flow/ford_fulkerson.hpp"

#include <vector>
#include <cstddef>
#include <algorithm>

#line 2 "graph/flow/flow_edge.hpp"

#include <iostream>
#line 5 "graph/flow/flow_edge.hpp"

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
#line 8 "graph/flow/ford_fulkerson.hpp"

template <class Flow> class ford_fulkerson {
    std::size_t s, t;
    int time;
    std::vector<std::vector<flow_edge<Flow>>> g;
    std::vector<int> ckd;

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
    ford_fulkerson()=default;
    ford_fulkerson(const ford_fulkerson&)=default;
    ford_fulkerson(ford_fulkerson&&)=default;
    ford_fulkerson&operator=(const ford_fulkerson&)=default;
    ford_fulkerson&operator=(ford_fulkerson&&)=default;
    ~ford_fulkerson()=default;

    ford_fulkerson(std::size_t n, std::size_t s_, int t_)
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
 * @title Ford−Fulkerson
 * @category graph
 * @category flow
 * @brief 計算量は $ O ( E f ) $ です。
 * @see https://en.wikipedia.org/wiki/Ford%E2%80%93Fulkerson_algorithm
 */
#line 4 "test/aoj-grl-6-a.test.cpp"

#line 6 "test/aoj-grl-6-a.test.cpp"

int main(){
    int n, m;
    std::cin >> n >> m;

    auto ff=ford_fulkerson<int>(n, 0, n-1);

    while(m--){
        int u, v, c;
        std::cin >> u >> v >> c;

        ff.insert(u, v, c);
    }

    std::cout<<ff.run()<<'\n';
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
