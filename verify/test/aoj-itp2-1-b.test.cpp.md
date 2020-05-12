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


# :heavy_check_mark: test/aoj-itp2-1-b.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj-itp2-1-b.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-12 20:29:34+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_1_B">https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_1_B</a>


## Depends on

* :heavy_check_mark: <a href="../../library/bbst/splay_tree.hpp.html">スプレー木 (Splay tree)</a>
* :heavy_check_mark: <a href="../../library/others/cstdint2.hpp.html">others/cstdint2.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_1_B"

#include <iostream>
#include <limits>

#include "../others/cstdint2.hpp"
#include "../bbst/splay_tree.hpp"

template <class Value> struct min_monoid_t {
    using value_type = Value;
    static value_type op(value_type l, value_type r) { return std::min(l, r); }
    static const value_type id() { return std::numeric_limits<Value>::max(); }
};

int main(){
    splay_tree<min_monoid_t<i32>> sp;

    usize q;
    std::cin >> q;
    while (q--) {
        i32 c;
        std::cin >> c;

        if (c==0) {
            i32 d, x;
            std::cin >> d >> x;

            if (d==0) {
                sp.push_front(x);
            }
            if (d==1) {
                sp.push_back(x);
            }
        }

        if (c==1) {
            usize i;
            std::cin >> i;

            std::cout << sp.get(i) << '\n';
        }

        if (c==2) {
            i32 d;
            std::cin >> d;

            if (d==0) {
                sp.pop_front();
            }
            if (d==1) {
                sp.pop_back();
            }
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 349, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=pathlib.Path.cwd())
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 172, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 282, in update
    self.update(self._resolve(pathlib.Path(included), included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 214, in update
    raise BundleError(path, i + 1, "#pragma once found in a non-first line")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: bbst/splay_tree.hpp: line 6: #pragma once found in a non-first line

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

