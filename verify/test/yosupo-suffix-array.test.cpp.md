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


# :heavy_check_mark: test/yosupo-suffix-array.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo-suffix-array.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-05 17:45:57+09:00


* see: <a href="https://judge.yosupo.jp/problem/suffixarray">https://judge.yosupo.jp/problem/suffixarray</a>


## Depends on

* :heavy_check_mark: <a href="../../library/string/suffix_array.hpp.html">string/suffix_array.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "../string/suffix_array.hpp"

#include <iostream>
#include <cassert>

int main(){
    std::string s;
    std::cin >> s;

    std::vector<std::size_t> sa = suffix_array(s);

    std::vector<long long> v(s.size());
    std::transform(s.begin(), s.end(), v.begin(), [](char c){ return c * 42; });
    assert( sa == suffix_array(v) );

    for (std::size_t i=0; i<s.size(); i++) {
        std::cout << (i?" ":"") << sa.at(i);
    }
    std::cout << '\n';
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo-suffix-array.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#line 2 "string/suffix_array.hpp"

#include <cstddef>
#include <vector>
#include <algorithm>
#include <numeric>

template <class Container, class=typename Container::value_type>
std::vector<std::size_t> suffix_array (Container const& s)
{
    if (s.empty())  return {};

    std::vector<std::size_t> c(s.size()), sa(s.size()), swp(s.size()), pos(s.size());

    // 1 文字目まで見てソートです。
    std::iota(std::begin(sa), std::end(sa), 0u);
    std::sort(std::begin(sa), std::end(sa), [&s](std::size_t i, std::size_t j) {
        return s.at(i)==s.at(j) ? i>j : s.at(i)<s.at(j); });

    // 1 文字目まで見た同値類です。
    // 1 文字しかないものは特別で、別同値類です。←ここが匠ポイントです。
    for (std::size_t i=1; i<s.size(); i++) {
        c.at(sa.at(i)) = sa.at(i-1)+1!=s.size() && s.at(sa.at(i-1))==s.at(sa.at(i))
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
        swp = sa;
        for (std::size_t i : sa) if (len <= i) {
            swp.at(pos.at(c.at(i-len))++) = i-len;
        }
        swp.swap(sa);

        // 同値類です。
        // ピッタリのものは特別で、別同値類です。←ここが匠ポイントです。
        swp.at(sa.at(0)) = 0;
        for (std::size_t i=1; i<s.size(); i++) {
            std::size_t x=sa.at(i-1), y=sa.at(i);

            swp.at(y) = x+len<s.size()
                && c.at(x)==c.at(y)
                && c.at(x+len)==c.at(y+len)
                ? swp.at(x)
                : i
                ;
        }
        swp.swap(c);
    }
    return sa;
}

#line 4 "test/yosupo-suffix-array.test.cpp"

#include <iostream>
#include <cassert>

int main(){
    std::string s;
    std::cin >> s;

    std::vector<std::size_t> sa = suffix_array(s);

    std::vector<long long> v(s.size());
    std::transform(s.begin(), s.end(), v.begin(), [](char c){ return c * 42; });
    assert( sa == suffix_array(v) );

    for (std::size_t i=0; i<s.size(); i++) {
        std::cout << (i?" ":"") << sa.at(i);
    }
    std::cout << '\n';
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

