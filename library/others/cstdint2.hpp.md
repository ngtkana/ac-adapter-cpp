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


# :heavy_check_mark: others/cstdint2.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5e2bab0ecb94c4ea40777733195abe1b">others</a>
* <a href="{{ site.github.repository_url }}/blob/master/others/cstdint2.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-12 20:04:26+09:00




## Required by

* :heavy_check_mark: <a href="../bbst/splay_tree.hpp.html">スプレー木 (Splay tree)</a>
* :heavy_check_mark: <a href="../graph/connectivity/tec_component.hpp.html">2-辺連結成分分解 (Two-edges components)</a>
* :heavy_check_mark: <a href="../graph/tree/tree_diameter.hpp.html">木の直径 (Diameer of tree)</a>
* :heavy_check_mark: <a href="../integral/mint.hpp.html">integral/mint.hpp</a>
* :heavy_check_mark: <a href="../integral/nt_trsf.hpp.html">NTT</a>
* :heavy_check_mark: <a href="../integral/residual_polynomials.hpp.html">剰余多項式 (residual polynomials)</a>
* :heavy_check_mark: <a href="cartesian_tree.hpp.html">カルテシアン木 (Cartesian Tree)</a>
* :warning: <a href="incremental_sum.hpp.html">others/incremental_sum.hpp</a>
* :heavy_check_mark: <a href="permutations.hpp.html">置換 (permutations)</a>
* :heavy_check_mark: <a href="../string/z_algorithm.hpp.html">Z algorithm <small>(string/z_algorithm.hpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../verify/integral/residual_polynomials.test.cpp.html">integral/residual_polynomials.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/others/cartesian_tree.yosupo-aplusb.test.cpp.html">others/cartesian_tree.yosupo-aplusb.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/others/permutations.yosupo-aplusb.test.cpp.html">others/permutations.yosupo-aplusb.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj-alds1-4-b.test.cpp.html">test/aoj-alds1-4-b.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj-grl-2-a.test.cpp.html">test/aoj-grl-2-a.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj-grl-2-b.test.cpp.html">test/aoj-grl-2-b.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj-grl-3-b.test.cpp.html">test/aoj-grl-3-b.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj-grl-5-a.test.cpp.html">test/aoj-grl-5-a.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj-itp2-1-a.test.cpp.html">test/aoj-itp2-1-a.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj-itp2-1-b.test.cpp.html">test/aoj-itp2-1-b.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj-itp2-1-c.test.cpp.html">test/aoj-itp2-1-c.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo-convolution_mod.test.cpp.html">test/yosupo-convolution_mod.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo-two-edge-connected-components.test.cpp.html">test/yosupo-two-edge-connected-components.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo-zalgorithm.test.cpp.html">test/yosupo-zalgorithm.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cstdint>

using i32 = std::int_least32_t;
using i64 = std::int_least64_t;
using u32 = std::uint_least32_t;
using u64 = std::uint_least64_t;
using usize = std::size_t;

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "others/cstdint2.hpp"

#include <cstdint>

using i32 = std::int_least32_t;
using i64 = std::int_least64_t;
using u32 = std::uint_least32_t;
using u64 = std::uint_least64_t;
using usize = std::size_t;

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

