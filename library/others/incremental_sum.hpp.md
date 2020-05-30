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


# :warning: others/incremental_sum.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5e2bab0ecb94c4ea40777733195abe1b">others</a>
* <a href="{{ site.github.repository_url }}/blob/master/others/incremental_sum.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-30 17:55:22+09:00




## Depends on

* :heavy_check_mark: <a href="cstdint2.hpp.html">others/cstdint2.hpp</a>
* :heavy_check_mark: <a href="vec.hpp.html">others/vec.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef OTHERS_INCREMENTAL_SUM_HPP
#define OTHERS_INCREMENTAL_SUM_HPP

#include "cstdint2.hpp"
#include "vec.hpp"
#include <algorithm>

template <class Group>
class incremental_sum {
    using this_type = incremental_sum<Group>;
    using group_type = Group;
    using value_type = typename group_type::value_type;

public:
    usize frozen;
    vec<value_type> table;

    incremental_sum()=default;
    incremental_sum(incremental_sum const&)=default;
    incremental_sum(incremental_sum&&)=default;
    incremental_sum& operator=(incremental_sum const&)=default;
    incremental_sum& operator=(incremental_sum&&)=default;
    ~incremental_sum()=default;

    incremental_sum(usize n)
        : frozen(0), table(n+1) {}

    incremental_sum(usize n, value_type x)
        : frozen(0), table(n+1, x)
    {
        std::partial_sum(table.begin(), table.end(), table.begin());
    }

    incremental_sum(vec<value_type> const& v)
        : frozen(0), table(v.size() + 1)
    {
        std::partial_sum(v.begin(), v.end(), table.begin() + 1);
    }

    this_type& set(usize i, value_type x) {
        assert(frozen == i);
        frozen++;
        table.at(i+1) = group_type::op(table.at(i), x);
        return *this;
    }

    value_type fold(usize l, usize r) {
        return group_type::sub(table.at(r), table.at(l));
    }

    vec<value_type> to_vec() const {
        vec<value_type> ans(table.size()-1);
        for (usize i=0; i<frozen; i++) {
            ans.at(i) = table.at(i+1) - table.at(i);
        }
        return ans;
    }
};

#endif

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "others/incremental_sum.hpp"



#line 2 "others/cstdint2.hpp"

#include <cstdint>

using i32 = std::int_least32_t;
using i64 = std::int_least64_t;
using u32 = std::uint_least32_t;
using u64 = std::uint_least64_t;
using usize = std::size_t;
#line 1 "others/vec.hpp"



#include <vector>

template <class T> using vec = std::vector<T>;


#line 6 "others/incremental_sum.hpp"
#include <algorithm>

template <class Group>
class incremental_sum {
    using this_type = incremental_sum<Group>;
    using group_type = Group;
    using value_type = typename group_type::value_type;

public:
    usize frozen;
    vec<value_type> table;

    incremental_sum()=default;
    incremental_sum(incremental_sum const&)=default;
    incremental_sum(incremental_sum&&)=default;
    incremental_sum& operator=(incremental_sum const&)=default;
    incremental_sum& operator=(incremental_sum&&)=default;
    ~incremental_sum()=default;

    incremental_sum(usize n)
        : frozen(0), table(n+1) {}

    incremental_sum(usize n, value_type x)
        : frozen(0), table(n+1, x)
    {
        std::partial_sum(table.begin(), table.end(), table.begin());
    }

    incremental_sum(vec<value_type> const& v)
        : frozen(0), table(v.size() + 1)
    {
        std::partial_sum(v.begin(), v.end(), table.begin() + 1);
    }

    this_type& set(usize i, value_type x) {
        assert(frozen == i);
        frozen++;
        table.at(i+1) = group_type::op(table.at(i), x);
        return *this;
    }

    value_type fold(usize l, usize r) {
        return group_type::sub(table.at(r), table.at(l));
    }

    vec<value_type> to_vec() const {
        vec<value_type> ans(table.size()-1);
        for (usize i=0; i<frozen; i++) {
            ans.at(i) = table.at(i+1) - table.at(i);
        }
        return ans;
    }
};



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

