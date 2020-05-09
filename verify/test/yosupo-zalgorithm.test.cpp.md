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
    - Last commit date: 2020-05-09 23:07:25+09:00


* see: <a href="https://judge.yosupo.jp/problem/zalgorithm">https://judge.yosupo.jp/problem/zalgorithm</a>


## Depends on

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

    auto z_array = z_algorhthm(s);

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

#include <cstddef>
#include <vector>
/*
 * @brief Z algorithm
 * @docs string/z_algorithm.md
 * @see https://snuke.hatenablog.com/entry/2014/12/03/214243
 * @see https://qiita.com/Pro_ktmr/items/16904c9570aa0953bf05
 * @see https://ei1333.github.io/luzhiled/snippets/string/z-algorithm.html
 */

template <class Container, class=typename Container::value_type>
std::vector<std::size_t> z_algorhthm (Container const& s)
{
    std::vector<std::size_t> z(s.size());

    if (s.empty()) {
        return z;
    }

    for (std::size_t i=1, j=0; i<s.size(); ) {
        for (; i+j<s.size() && s.at(j)==s.at(i+j); j++);
        z.at(i) = j;

        if (j==0) {
            i++;
            continue;
        }

        std::size_t k=1;
        for (; i+k<s.size() && k+z.at(k)<j; k++) {
            z.at(i+k) = z.at(k);
        }
        i += k;
        j -= k;
    }
    z.at(0) = s.size();

    return z;
}
#line 4 "test/yosupo-zalgorithm.test.cpp"

#include <iostream>

int main(){
    std::string s;
    std::cin >> s;

    auto z_array = z_algorhthm(s);

    for (std::size_t i=0; i<s.length(); i++) {
        std::cout << (i ? " " : "") << z_array.at(i);
    }
    std::cout << '\n';
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

