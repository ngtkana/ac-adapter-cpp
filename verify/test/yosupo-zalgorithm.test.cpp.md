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


# :heavy_check_mark: test/yosupo-zalgorithm.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo-zalgorithm.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-30 17:55:01+09:00


* see: <a href="https://judge.yosupo.jp/problem/zalgorithm">https://judge.yosupo.jp/problem/zalgorithm</a>


## Depends on

* :heavy_check_mark: <a href="../../library/others/cstdint2.hpp.html">others/cstdint2.hpp</a>
* :heavy_check_mark: <a href="../../library/others/vec.hpp.html">others/vec.hpp</a>
* :heavy_check_mark: <a href="../../library/string/z_algorithm.hpp.html">Z algorithm <small>(string/z_algorithm.hpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../string/z_algorithm.hpp"

#include <iostream>

int main(){
    std::string s;
    std::cin >> s;

    auto z_array = z_algorithm(s);

    for (std::size_t i=0; i<s.length(); i++) {
        std::cout << (i ? " " : "") << z_array.at(i);
    }
    std::cout << '\n';
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo-zalgorithm.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#line 2 "string/z_algorithm.hpp"

#line 1 "others/vec.hpp"



#include <vector>

template <class T> using vec = std::vector<T>;


#line 2 "others/cstdint2.hpp"

#include <cstdint>

using i32 = std::int_least32_t;
using i64 = std::int_least64_t;
using u32 = std::uint_least32_t;
using u64 = std::uint_least64_t;
using usize = std::size_t;
#line 5 "string/z_algorithm.hpp"

/*
 * @brief Z algorithm
 * @docs string/z_algorithm.md
 * @see https://snuke.hatenablog.com/entry/2014/12/03/214243
 * @see https://qiita.com/Pro_ktmr/items/16904c9570aa0953bf05
 * @see https://ei1333.github.io/luzhiled/snippets/string/z-algorithm.html
 */

template <class Container, class=typename Container::value_type>
std::vector<usize> z_algorithm (Container const& s) {
    vec<usize> a(s.length());
    if (s.empty()) return a;
    a.at(0) = s.length();
    for (usize i=1, j=1, k; i<s.length(); i=k) {
        for (; j<s.length() && s.at(j-i)==s.at(j); j++);
        a.at(i) = j-i;
        if (j==i) j++;
        for (k=i+1; k<j && k+a.at(k-i)!=j; k++) {
            a.at(k) = std::min(j-k, a.at(k-i));
        }
    }
    return a;
}
#line 4 "test/yosupo-zalgorithm.test.cpp"

#include <iostream>

int main(){
    std::string s;
    std::cin >> s;

    auto z_array = z_algorithm(s);

    for (std::size_t i=0; i<s.length(); i++) {
        std::cout << (i ? " " : "") << z_array.at(i);
    }
    std::cout << '\n';
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

