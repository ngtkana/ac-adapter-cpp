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


# :heavy_check_mark: test/hello-world/suffix-array.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#a8d234c3fc8ceb165fb4b5ed3aa77415">test/hello-world</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/hello-world/suffix-array.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-05 16:34:37+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/string/suffix_array.hpp.html">string/suffix_array.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include "../../string/suffix_array.hpp"

#include <iostream>
#include <cassert>

int main() {

    std::string s = "abracadabra";
    std::vector<std::size_t> result = suffix_array(s);
    std::vector<std::size_t> expected = { 10, 7, 0, 3, 5, 8, 1, 4, 6, 9, 2 };
    assert( result == expected );

    std::vector<long long> v(s.size());
    std::transform( s.begin(), s.end(), v.begin(), [](char c){ return c * 42; });
    result = suffix_array(v);
    assert( result == expected );

    std::cout << "Hello World" << '\n';
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/hello-world/suffix-array.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#line 2 "string/suffix_array.hpp"

#include <cstddef>
#include <vector>
#include <algorithm>
#include <numeric>

template <class Container, class=typename Container::value_type>
std::vector<std::size_t> suffix_array (Container const& s)
{
    std::vector<std::size_t> c(s.size()), sa(s.size()), swp(s.size()), pos(s.size());

    // 1 文字目まで見てソートです。
    std::iota(std::begin(sa), std::end(sa), 0u);
    std::sort(std::begin(sa), std::end(sa), [&s](std::size_t i, std::size_t j) {
        return s.at(i)==s.at(j) ? i>j : s.at(i)<s.at(j); });

    // 1 文字目まで見た同値類です。
    // 1 文字しかないものは特別で、別同値類です。←ここが匠ポイントです。
    for (std::size_t i=1; i<s.size(); i++) {
        c.at(sa.at(i)) = 1<i && s.at(sa.at(i-1))==s.at(sa.at(i))
            ? c.at(sa.at(i-1))
            : i
            ;
    }

    // 2*len 文字目まで見ましょう。
    for (std::size_t len=1; len<s.size(); len<<=1) {
        // 同値類ごとに、次に入る場所を管理です。
        std::iota(std::begin(pos), std::end(pos), 0u);

        // ソートです。
        // 長さの短いものとぴったりのものは、別です。
        for (std::size_t i=s.size()-len; i<s.size(); i++) {
            swp.at(c.at(i)) = i;
        }
        for (std::size_t i : sa) if (len <= i) {
            if (len <= i) {
                swp.at(pos.at(c.at(i-len))++) = i-len;
            }
        }
        swp.swap(sa);

        // 同値類です。
        // ピッタリのものは特別で、別同値類です。←ここが匠ポイントです。
        swp.at(sa.at(0)) = 0;
        for (std::size_t i=1; i<s.size(); i++) {
            swp.at(sa.at(i)) = sa.at(i-1)+len<s.size()
                && c.at(sa.at(i-1))==c.at(sa.at(i))
                && c.at(sa.at(i-1)+len)==c.at(sa.at(i)+len)
                ? c.at(sa.at(i-1))
                : i
                ;
        }
        swp.swap(c);
    }
    return sa;
}

#line 4 "test/hello-world/suffix-array.test.cpp"

#include <iostream>
#include <cassert>

int main() {

    std::string s = "abracadabra";
    std::vector<std::size_t> result = suffix_array(s);
    std::vector<std::size_t> expected = { 10, 7, 0, 3, 5, 8, 1, 4, 6, 9, 2 };
    assert( result == expected );

    std::vector<long long> v(s.size());
    std::transform( s.begin(), s.end(), v.begin(), [](char c){ return c * 42; });
    result = suffix_array(v);
    assert( result == expected );

    std::cout << "Hello World" << '\n';
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

