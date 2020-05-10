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


# :heavy_check_mark: graph/edge.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/edge.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-10 14:26:17+09:00




## Required by

* :heavy_check_mark: <a href="shortest_path/dijkstra.hpp.html">ダイクストラ法 (Dijkstra)</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj-grl-1-a.test.cpp.html">test/aoj-grl-1-a.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

