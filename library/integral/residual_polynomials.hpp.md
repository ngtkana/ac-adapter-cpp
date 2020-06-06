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


# :heavy_check_mark: 剰余多項式 (residual polynomials)

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#25aa2761448ea05599418ee93dd1d5c5">integral</a>
* <a href="{{ site.github.repository_url }}/blob/master/integral/residual_polynomials.hpp">View this file on GitHub</a>
    - Last commit date: 2020-06-06 12:44:57+09:00




## 概要

定数項が $ 0 $ でない、次数 $ 1 $ 以上の多項式 f ( q ) \in K [ q ] $ による剰余環上の演算です。

また、最高次も $ 0 $ でないと受け付けないようになっております。


## メンバ変数

- $ \mathtt { qd } $: $ d $ が $ f $ の字数だとして、 $ q ^ d $ を $ f $ で割ったあまりです。

- $ \mathtt { qinv } $: $ q $ の逆元です。


## メンバ関数

- $ \mathtt{ normalize(a) } $: $ a $ のサイズを調整します。

- $ \mathtt{ mul(a, b) } $: $ a b \bmod f $ です。

- $ \mathtt{ pow(a, b) } $: $ a ^  b \bmod f $ です。


## 例：漸化式

$ a $ が漸化式 $ a _ { n + d } = \sum _ { i = 1 } ^ d c _ { i } a _ { n + d - i } $ （ただし、$ c _ { d } \neq 0 $）に従うとしましょう。そしてその母関数を $ A $ と書きます。
さらにこれを配る DP で計算するときの初期値を $ P _ A $（これは $ d $ 次未満です。）、$ Q (q) = 1 - \sum _ { i = 1 } ^ d c _ { i } q ^ i $ と置くと、$ A = P _ A / Q $ となります。

さて、$ n $ 番目を求めるために、$ A $ を $ n $ 回シフトしたものを $ B $ と置きましょう。これも同じ漸化式に従いますから、$ P _ B = B \cdot Q $ も $ d $ 次未満です。
ここで、$ A = q^n \cdot B + A \vert _ { < d } $ ですから、これに $ Q $ を掛けると、$ P _ A = q ^ n \cdot O _ B + A \vert _ { < d } \cdot Q $ が得られます。
さらに $ Q $ による剰余をとると、$ P _ A = q ^ n \cdot P _ B \pmod Q $ ですから、$ P _ B = q ^ { - n } \cdot P _ A \pmod Q $ となります。
一方 $ P _ B $ は $ d $ 次未満であることもわかっていますから、これで確定することができます。

ところでいま知りたかったのは $ a _ n = [1] B $ でした。しかし、$ Q $ は定数項が $ 1 $ ですから、これは $ [1] P _ B $ に等しいです。




## Depends on

* :heavy_check_mark: <a href="../others/cstdint2.hpp.html">others/cstdint2.hpp</a>
* :heavy_check_mark: <a href="../others/vec.hpp.html">others/vec.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/integral/residual_polynomials.test.cpp.html">integral/residual_polynomials.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/*
 * @title 剰余多項式 (residual polynomials)
 * @docs integral/residual_polynomials.md
 */

#pragma once

#include <cassert>
#include <cstddef>
#include <utility>
#include <cmath>
#include <type_traits>
#include <iostream>

#include "../others/cstdint2.hpp"
#include "../others/vec.hpp"

template <class Mint>
class resudual_polynomials {
    using mint_type = Mint;

public:
    vec<mint_type> f, qinv, qd;

    resudual_polynomials()=default;
    resudual_polynomials(resudual_polynomials const&)=default;
    resudual_polynomials(resudual_polynomials&&)=default;
    resudual_polynomials& operator=(resudual_polynomials const&)=default;
    resudual_polynomials& operator=(resudual_polynomials&&)=default;
    ~resudual_polynomials()=default;

    resudual_polynomials(vec<mint_type> const& f_)
        : f(f_)
    {
        assert(usize{2} <= f.size());
        qinv.resize(f.size()-1), qd.resize(f.size()-1);
        mint_type x = -f.front().inv(), y = -f.back().inv();
        for (usize i=0; i<qinv.size(); i++) {
            qinv.at(i) = x * f.at(i+1);
            qd.at(i) = y * f.at(i);
        }
    }

    vec<mint_type>& normalize(vec<mint_type>& a) {
        while (a.size() < qd.size()) a.push_back(0);
        while (qd.size() < a.size()) {
            mint_type y = a.back(); a.pop_back();
            for (usize i=0; i<qd.size(); i++) {
                a.at(a.size() - qd.size() + i) += y * qd.at(i);
            }
        }
        return a;
    }

    vec<mint_type> mul(vec<mint_type> a, vec<mint_type> b) {
        normalize(a), normalize(b);
        vec<mint_type> c(qd.size() * 2 - 1);
        for (usize i=0; i<qd.size(); i++) for (usize j=0; j<qd.size(); j++) {
            c.at(i+j) += a.at(i) * b.at(j);
        }
        return normalize(c);
    }

    vec<mint_type> pow(vec<mint_type> a, i64 b) {
        vec<mint_type> ans = {1};
        for(; b; a = mul(a, a), b>>=1) if (b & i64{1}) ans = mul(ans, a);
        return ans;
    }
};


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
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 239, in update
    raise BundleErrorAt(path, i + 1, "#pragma once found in a non-first line")
onlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: integral/residual_polynomials.hpp: line 6: #pragma once found in a non-first line

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

