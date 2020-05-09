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


# :warning: string/z_algorithm.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/z_algorithm.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-09 22:50:08+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cstddef>
#include <vector>

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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "string/z_algorithm.hpp"

#include <cstddef>
#include <vector>

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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

