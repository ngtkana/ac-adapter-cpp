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


# :heavy_check_mark: 置換 (permutations)

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5e2bab0ecb94c4ea40777733195abe1b">others</a>
* <a href="{{ site.github.repository_url }}/blob/master/others/permutations.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-27 03:31:33+09:00




## あるもの

- $ \mathtt { mul \unicode { 95 } assign \unicode { 95 } from \unicode { 95 } the \unicode { 95 } right ( a, b ) } $:
<var> a </var> を <var> ba </var> に置き換えます。post-composition です。引数の順番に注意です。

- $ \mathtt { mul (a, b) } $: $ a b $ を返します。

- $ \mathtt { inv (a) } $: $ a ^ { -1 } $ を返します。

- $ \mathtt { pow (a, b) } $: $ a ^ b $ を返します。<var> b </var> は $ 0 $ 以上でお願いします。


## Depends on

* :heavy_check_mark: <a href="cstdint2.hpp.html">others/cstdint2.hpp</a>
* :heavy_check_mark: <a href="vec.hpp.html">others/vec.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/others/permutations.yosupo-aplusb.test.cpp.html">others/permutations.yosupo-aplusb.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/*
 * @title 置換 (permutations)
 * @docs others/permutations.md
 */
#ifndef OTHERS_PERMUPTATIONS_HPP
#define OTHERS_PERMUPTATIONS_HPP

#include <cassert>
#include <algorithm>
#include <numeric>

#include "cstdint2.hpp"
#include "vec.hpp"

struct permutations {
    static vec<usize>& mul_assign_from_the_right(vec<usize>& a, vec<usize> const& b) {
        for (usize i=0; i<a.size(); i++) {
            a.at(i) = b.at(a.at(i));
        }
        return a;
    }

    static vec<usize> mul(vec<usize> const& a, vec<usize> const& b) {
        assert(a.size()==b.size());
        vec<usize> ans(a.size());
        for (usize i=0; i<a.size(); i++) {
            ans.at(i) = a.at(b.at(i));
        }
        return ans;
    }

    static vec<usize> inv(vec<usize> const& a) {
        vec<usize> ans(a.size());
        for (usize i=0; i<a.size(); i++) {
            ans.at(a.at(i)) = i;
        }
        return ans;
    }

    template <class T>
    static vec<usize> pow(vec<usize> a, T b) {
        vec<usize> ans(a.size());
        std::iota(ans.begin(), ans.end(), 0u);
        for (; b; b>>=1) {
            if (b&1) ans = mul(ans, a);
            a = mul(a, a);
        }
        return ans;
    }

    static u64 merge_sort(vec<usize>& a) {
        if (a.size() <= 1u) return 0u;
        vec<usize> b(a.begin(), a.begin()+a.size()/2), c(a.begin()+a.size()/2, a.end());
        u64 ans = merge_sort(b) + merge_sort(c);
        for (usize i=0, j=0; i<b.size() || j<c.size(); ) {
            if (j==c.size() || (i<b.size() && b.at(i) < c.at(j))) {
                a.at(i+j) = b.at(i);
                i++;
            } else {
                ans += b.size() - i;
                a.at(i+j) = c.at(j);
                j++;
            }
        }
        return ans;
    }

    static u64 inversion_number(vec<usize> a) {
        return merge_sort(a);
    }
};

#endif


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 349, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=pathlib.Path.cwd())
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 185, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 306, in update
    raise BundleErrorAt(path, i + 1, "unable to process #include in #if / #ifdef / #ifndef other than include guards")
onlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: others/permutations.hpp: line 12: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

