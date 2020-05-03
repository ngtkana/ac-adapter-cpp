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


# :heavy_check_mark: graph/flow/flow_edge.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#2af6c4bb6ad7cfa010303133dc15971f">graph/flow</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/flow/flow_edge.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-03 15:19:31+09:00




## Required by

* :heavy_check_mark: <a href="dinic.hpp.html">Dinic</a>
* :heavy_check_mark: <a href="ford_fulkerson.hpp.html">Ford−Fulkerson</a>
* :heavy_check_mark: <a href="relabel_to_front.hpp.html">Push-relabel by Relabel-to-front selection rule</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj-grl-6-a-1.test.cpp.html">test/aoj-grl-6-a-1.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/aoj-grl-6-a-2.test.cpp.html">test/aoj-grl-6-a-2.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/aoj-grl-6-a.test.cpp.html">test/aoj-grl-6-a.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

