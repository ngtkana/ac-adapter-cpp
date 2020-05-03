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


# :heavy_check_mark: Push-relabel by Relabel-to-front selection rule

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#cff5497121104c2b8e0cb41ed2083a9b">flow</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/flow/relabel_to_front.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-04 02:33:32+09:00


* see: <a href="https://en.wikipedia.org/wiki/Push%E2%80%93relabel_maximum_flow_algorithm">https://en.wikipedia.org/wiki/Push%E2%80%93relabel_maximum_flow_algorithm</a>


## Depends on

* :heavy_check_mark: <a href="flow_edge.hpp.html">graph/flow/flow_edge.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj-grl-6-a-2.test.cpp.html">test/aoj-grl-6-a-2.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "flow_edge.hpp"

#include <cstddef>
#include <vector>
#include <algorithm>
#include <list>
#include <cassert>

template <class Flow> struct relabel_to_front {
    std::size_t s, t;
    std::vector<std::vector<flow_edge<Flow>>> g;
    std::vector<unsigned> h;
    std::vector<Flow> ex;
    std::list<std::size_t> list;

    relabel_to_front()=default;
    relabel_to_front(relabel_to_front const&)=default;
    relabel_to_front(relabel_to_front&&)=default;
    relabel_to_front& operator=(relabel_to_front const&)=default;
    relabel_to_front& operator=(relabel_to_front&&)=default;
    ~relabel_to_front()=default;

    relabel_to_front(std::size_t n, std::size_t s_, std::size_t t_)
        : s(s_), t(t_), g(n), h(n), ex(n, zero())
    {
        h.at(0) = n;
        for (std::size_t i=0; i<n; i++) if (i!=s && i!=t) {
            list.push_back(i);
        }
    }

    void insert(std::size_t u, std::size_t v, Flow w) {
        std::size_t su = g.at(u).size();
        std::size_t sv = g.at(v).size();
        g.at(u).emplace_back(v, sv, w);
        g.at(v).emplace_back(u, su, 0);
    }

    std::size_t size() const { return g.size(); }

    static Flow zero() { return Flow{ 0 }; }

    void initialize_preflow() {
        for (auto& e : g.at(s)) {
            Flow d = e.cap;
            ex.at(s) -= d;
            ex.at(e.to) += d;
            e.cap -= d;
            g.at(e.to).at(e.rev).cap += d;
        }
    }

    void push(std::size_t u, flow_edge<Flow>& e) {
        assert(0<ex.at(u) && zero()<e.cap && h.at(u)==h.at(e.to)+1);

        Flow d=std::min(ex.at(u), e.cap);
        e.cap -= d;
        g.at(e.to).at(e.rev).cap += d;
        ex.at(u) -= d;
        ex.at(e.to) += d;

    }

    void relabel(std::size_t u) {
        assert(0<ex.at(u));

        unsigned min = 2*size();
        for (flow_edge<Flow> const& e : g.at(u)) {
            if (e.cap!=zero()) {
                assert(h.at(u) <= h.at(e.to));
                min = std::min(min, h.at(e.to));
            }
        }
        h.at(u) = min + 1;
    }

    bool discharge(std::size_t u) {
        bool relabelled = false;
        for (std::size_t c=0; ex.at(u); c++) {
            if (c==g.at(u).size()) {
                relabel(u);
                c=0;
                relabelled = true;
            }

            flow_edge<Flow>& e = g.at(u).at(c);
            if (zero()<e.cap && h.at(u)==h.at(e.to)+1) {
                push(u, e);
            }
        }
        return relabelled;
    }

    Flow run() {
        initialize_preflow();

        for (auto it=list.begin(); it!=list.end(); it++) {
            if (discharge(*it)) {
                list.push_front(*it);
                list.erase(it);
                it = list.begin();
            }
        }

        return ex.at(t);
    }

    std::vector<std::vector<flow_edge<Flow>>> to_vec() const {
        std::vector<std::vector<flow_edge<Flow>>> ans(size());
        for (std::size_t i=0; i<size(); i++) {
            ans.at(i) = g.at(i);
        }
        return ans;
    }
};

/*
 * @title Push-relabel by Relabel-to-front selection rule
 * @category graph
 * @category flow
 * @docs docs/relabel_to_front
 * @see https://en.wikipedia.org/wiki/Push%E2%80%93relabel_maximum_flow_algorithm
 */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph/flow/relabel_to_front.hpp"

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
#line 4 "graph/flow/relabel_to_front.hpp"

#line 6 "graph/flow/relabel_to_front.hpp"
#include <vector>
#include <algorithm>
#include <list>
#include <cassert>

template <class Flow> struct relabel_to_front {
    std::size_t s, t;
    std::vector<std::vector<flow_edge<Flow>>> g;
    std::vector<unsigned> h;
    std::vector<Flow> ex;
    std::list<std::size_t> list;

    relabel_to_front()=default;
    relabel_to_front(relabel_to_front const&)=default;
    relabel_to_front(relabel_to_front&&)=default;
    relabel_to_front& operator=(relabel_to_front const&)=default;
    relabel_to_front& operator=(relabel_to_front&&)=default;
    ~relabel_to_front()=default;

    relabel_to_front(std::size_t n, std::size_t s_, std::size_t t_)
        : s(s_), t(t_), g(n), h(n), ex(n, zero())
    {
        h.at(0) = n;
        for (std::size_t i=0; i<n; i++) if (i!=s && i!=t) {
            list.push_back(i);
        }
    }

    void insert(std::size_t u, std::size_t v, Flow w) {
        std::size_t su = g.at(u).size();
        std::size_t sv = g.at(v).size();
        g.at(u).emplace_back(v, sv, w);
        g.at(v).emplace_back(u, su, 0);
    }

    std::size_t size() const { return g.size(); }

    static Flow zero() { return Flow{ 0 }; }

    void initialize_preflow() {
        for (auto& e : g.at(s)) {
            Flow d = e.cap;
            ex.at(s) -= d;
            ex.at(e.to) += d;
            e.cap -= d;
            g.at(e.to).at(e.rev).cap += d;
        }
    }

    void push(std::size_t u, flow_edge<Flow>& e) {
        assert(0<ex.at(u) && zero()<e.cap && h.at(u)==h.at(e.to)+1);

        Flow d=std::min(ex.at(u), e.cap);
        e.cap -= d;
        g.at(e.to).at(e.rev).cap += d;
        ex.at(u) -= d;
        ex.at(e.to) += d;

    }

    void relabel(std::size_t u) {
        assert(0<ex.at(u));

        unsigned min = 2*size();
        for (flow_edge<Flow> const& e : g.at(u)) {
            if (e.cap!=zero()) {
                assert(h.at(u) <= h.at(e.to));
                min = std::min(min, h.at(e.to));
            }
        }
        h.at(u) = min + 1;
    }

    bool discharge(std::size_t u) {
        bool relabelled = false;
        for (std::size_t c=0; ex.at(u); c++) {
            if (c==g.at(u).size()) {
                relabel(u);
                c=0;
                relabelled = true;
            }

            flow_edge<Flow>& e = g.at(u).at(c);
            if (zero()<e.cap && h.at(u)==h.at(e.to)+1) {
                push(u, e);
            }
        }
        return relabelled;
    }

    Flow run() {
        initialize_preflow();

        for (auto it=list.begin(); it!=list.end(); it++) {
            if (discharge(*it)) {
                list.push_front(*it);
                list.erase(it);
                it = list.begin();
            }
        }

        return ex.at(t);
    }

    std::vector<std::vector<flow_edge<Flow>>> to_vec() const {
        std::vector<std::vector<flow_edge<Flow>>> ans(size());
        for (std::size_t i=0; i<size(); i++) {
            ans.at(i) = g.at(i);
        }
        return ans;
    }
};

/*
 * @title Push-relabel by Relabel-to-front selection rule
 * @category graph
 * @category flow
 * @docs docs/relabel_to_front
 * @see https://en.wikipedia.org/wiki/Push%E2%80%93relabel_maximum_flow_algorithm
 */

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

