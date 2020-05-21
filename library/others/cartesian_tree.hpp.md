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


# :heavy_check_mark: カルテシアン木 (Cartesian Tree)

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5e2bab0ecb94c4ea40777733195abe1b">others</a>
* <a href="{{ site.github.repository_url }}/blob/master/others/cartesian_tree.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-22 00:44:05+09:00




## Depends on

* :heavy_check_mark: <a href="cstdint2.hpp.html">others/cstdint2.hpp</a>
* :heavy_check_mark: <a href="vec.hpp.html">others/vec.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/others/cartesian_tree.yosupo-aplusb.test.cpp.html">others/cartesian_tree.yosupo-aplusb.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/*
 * @title カルテシアン木 (Cartesian Tree)
 * @docs others/cartesian_tree.hpp
 */

#include <utility>
#include <functional>

#include "cstdint2.hpp"
#include "vec.hpp"

template <class T, class Comp=std::less<T>>
auto cartesian_tree(vec<T> const& a, Comp const& comp={}) {
    usize n = a.size();
    vec<T> stack;
    vec<usize> p(n, n);
    for (usize i=0; i<n; i++) {
        usize j = n;
        while (!stack.empty() && comp(a.at(i), a.at(stack.back()))) {
            j = stack.back();
            stack.pop_back();
        }
        if (j!=n) {
            p.at(j) = i;
        }
        if (!stack.empty()) {
            p.at(i) = stack.back();
        }
        stack.push_back(i);
    }

    usize root = n;
    vec<vec<usize>> g(n);
    for (usize i=0; i<n; i++) {
        if (p.at(i)==n) {
            root = i;
        } else {
            g.at(p.at(i)).push_back(i);
        }
    }
    return std::make_pair(root, g);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "others/cartesian_tree.hpp"
/*
 * @title カルテシアン木 (Cartesian Tree)
 * @docs others/cartesian_tree.hpp
 */

#include <utility>
#include <functional>

#line 2 "others/cstdint2.hpp"

#include <cstdint>

using i32 = std::int_least32_t;
using i64 = std::int_least64_t;
using u32 = std::uint_least32_t;
using u64 = std::uint_least64_t;
using usize = std::size_t;
#line 1 "others/vec.hpp"



#include <vector>

template <class T> using vec = std::vector<T>;


#line 11 "others/cartesian_tree.hpp"

template <class T, class Comp=std::less<T>>
auto cartesian_tree(vec<T> const& a, Comp const& comp={}) {
    usize n = a.size();
    vec<T> stack;
    vec<usize> p(n, n);
    for (usize i=0; i<n; i++) {
        usize j = n;
        while (!stack.empty() && comp(a.at(i), a.at(stack.back()))) {
            j = stack.back();
            stack.pop_back();
        }
        if (j!=n) {
            p.at(j) = i;
        }
        if (!stack.empty()) {
            p.at(i) = stack.back();
        }
        stack.push_back(i);
    }

    usize root = n;
    vec<vec<usize>> g(n);
    for (usize i=0; i<n; i++) {
        if (p.at(i)==n) {
            root = i;
        } else {
            g.at(p.at(i)).push_back(i);
        }
    }
    return std::make_pair(root, g);
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

