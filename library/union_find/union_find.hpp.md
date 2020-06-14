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


# :warning: union_find/union_find.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#bc2964fb507ef1d27a388613d11607e7">union_find</a>
* <a href="{{ site.github.repository_url }}/blob/master/union_find/union_find.hpp">View this file on GitHub</a>
    - Last commit date: 2020-06-15 03:45:00+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
class union_find {
    std::vector<i32> p;

    public:
    union_find()=default;
    union_find(union_find const&)=default;
    union_find(union_find&&)=default;
    union_find& operator=(union_find const&)=default;
    union_find& operator=(union_find&&)=default;
    ~union_find()=default;

    union_find(i32 n)
        : p(n, -1) {}

    auto get_i32ernal_table() const { return p; }
    bool is_root(i32 i) const { return p.at(i) < 0; }
    i32 root(i32 i) { return is_root(i) ? i : p.at(i) = root(p.at(i)); }
    i32 size(i32 i) { return -p.at(root(i)); }
    usize size() const { return p.size(); }

    bool unite(i32 i, i32 j) {
        i = root(i);
        j = root(j);
        if (i==j) return false;
        if (size(i) > size(j)) std::swap(i, j);

        p.at(j) += p.at(i);
        p.at(i) = j;
        return true;
    }

    std::string debug() {
        vec<vec<i32>> mems(size());
        for (i32 i=0; i<(i32)size(); i++) mems.at(root(i)).push_back(i);
        mems.resize(std::remove_if(mems.begin(), mems.end(), [](auto&& v){ return v.empty(); }) - mems.begin());
        std::stringstream ss;
        ss << '{';
        for (usize i=0; i<mems.size(); i++) {
            ss << (i ? "|" : "");
            auto&& v = mems.at(i);
            for (usize j=0; j<v.size(); j++) {
                ss << (j ? "," : "") << v.at(j);
            }
        }
        ss << '}';
        return ss.str();
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "union_find/union_find.hpp"
class union_find {
    std::vector<i32> p;

    public:
    union_find()=default;
    union_find(union_find const&)=default;
    union_find(union_find&&)=default;
    union_find& operator=(union_find const&)=default;
    union_find& operator=(union_find&&)=default;
    ~union_find()=default;

    union_find(i32 n)
        : p(n, -1) {}

    auto get_i32ernal_table() const { return p; }
    bool is_root(i32 i) const { return p.at(i) < 0; }
    i32 root(i32 i) { return is_root(i) ? i : p.at(i) = root(p.at(i)); }
    i32 size(i32 i) { return -p.at(root(i)); }
    usize size() const { return p.size(); }

    bool unite(i32 i, i32 j) {
        i = root(i);
        j = root(j);
        if (i==j) return false;
        if (size(i) > size(j)) std::swap(i, j);

        p.at(j) += p.at(i);
        p.at(i) = j;
        return true;
    }

    std::string debug() {
        vec<vec<i32>> mems(size());
        for (i32 i=0; i<(i32)size(); i++) mems.at(root(i)).push_back(i);
        mems.resize(std::remove_if(mems.begin(), mems.end(), [](auto&& v){ return v.empty(); }) - mems.begin());
        std::stringstream ss;
        ss << '{';
        for (usize i=0; i<mems.size(); i++) {
            ss << (i ? "|" : "");
            auto&& v = mems.at(i);
            for (usize j=0; j<v.size(); j++) {
                ss << (j ? "," : "") << v.at(j);
            }
        }
        ss << '}';
        return ss.str();
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

