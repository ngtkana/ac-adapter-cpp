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


# :heavy_check_mark: HL 分解 (heavy-light decomposition)

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#28790b6202284cbbffc9d712b59f4b80">graph/tree</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/tree/hl_decomposition.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-11 20:28:07+09:00




## 構築

### 方法 1

insert 戦略です。

- $ \mathtt{ hl \unicode{95} decomposition ( n ) } $: サイズを指定です。この時点では空グラフです。

- $ \mathtt{ insert ( i, j )} $: 無向辺（有向辺 2 本）を張ります。

- $ \mathtt{ build( root ) } $: 構築をします。

構築済みかどうかのフラグを管理していて、2 回構築をすると実行時エラーになるようになっています。


### 方法 2

グラフと根を渡します。

- $ \mathtt{ hl \unicode{95} decomposition ( g, root ) } $


## アクセス

- $ vid $: 頂点番号から時刻へ

- $ head $: light edge を伝って行ける一番上にです。キーもバリューも時刻ではなく頂点番号です。

- $ g $: 中身のグラフです。構築済みの場合は、親が消されています。


## 対応できるグラフ

連結で単純な木です。

親への辺は、あってもなくてもよく、ある場合は $ \mathtt{ build } $ の中で消されます。



## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj-grl-5-d.test.cpp.html">test/aoj-grl-5-d.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/*
 * @title HL 分解 (heavy-light decomposition)
 * @docs graph/tree/hl_decomposition.md
 */

#pragma once

#include <cassert>
#include <cstddef>
#include <utility>
#include <algorithm>
#include <vector>

class hl_decomposition {

private:
    bool built = false;
    std::size_t time;

    void erase_prt_dfs(std::size_t x, std::size_t p)
    {
        auto&& v = g.at(x);
        auto p_found = std::find(v.begin(), v.end(), p);
        if (p_found!= v.end()) v.erase(p_found);
        for (std::size_t& y : v) {
            erase_prt_dfs(y, x);
        }
    }

    void size_dfs(std::size_t x)
    {
        auto&& v = g.at(x);
        for (std::size_t& y : v) {
            size_dfs(y);
            sz.at(x) += sz.at(y);
            if (sz.at(v.front()) < sz.at(y)) {
                std::swap(v.front(), y);
            }
        }
    }

    void head_dfs(std::size_t x)
    {
        vid.at(x) = time++;
        auto&& v = g.at(x);

        for (std::size_t y : v) {
            head.at(y) = y==v.front()
                ? head.at(x)
                : y
                ;
            head_dfs(y);
        }
    }

public:
    std::vector<std::size_t> sz, head, vid;
    std::vector<std::vector<std::size_t>> g;

    hl_decomposition()=default;
    hl_decomposition(hl_decomposition const&)=default;
    hl_decomposition(hl_decomposition&&)=default;
    hl_decomposition& operator=(hl_decomposition const&)=default;
    hl_decomposition& operator=(hl_decomposition&&)=default;
    ~hl_decomposition()=default;

    hl_decomposition(std::vector<std::vector<std::size_t>> const& g_, std::size_t root)
        : g(g_)
    {
        assert(root < size());
        build(root);
    }

    hl_decomposition(std::size_t n) : g(n) {}

    void insert(std::size_t u, std::size_t v) {
        assert(u < size() && v < size());
        g.at(u).push_back(v);
        g.at(v).push_back(u);
    }

    void build(std::size_t root)
    {
        assert(!std::exchange(built, true));
        assert(root < size());

        time = 0;
        sz.assign(size(), 1u);
        head.resize(size());
        vid.resize(size());

        head.at(root) = root;

        erase_prt_dfs(root, root);
        size_dfs(root);
        head_dfs(root);
    }

    std::size_t size() const { return g.size(); }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 349, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=pathlib.Path.cwd())
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 172, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 214, in update
    raise BundleError(path, i + 1, "#pragma once found in a non-first line")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: graph/tree/hl_decomposition.hpp: line 6: #pragma once found in a non-first line

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

