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


# :heavy_check_mark: test/aoj-grl-2-a.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj-grl-2-a.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 10:58:44+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_A">https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_A</a>


## Depends on

* :heavy_check_mark: <a href="../../library/bbst/splay_tree.hpp.html">bbst/splay_tree.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_A"

#include "../bbst/splay_tree.hpp"

#include <iostream>
#include <vector>
#include <tuple>
#include <limits>

// min-monoid{{{
template <class Value> struct min_monoid_t {
    using value_type = Value;
    static value_type op(value_type l, value_type r) { return std::min(l, r); }
    static const value_type id() { return std::numeric_limits<value_type>::max(); }
};
/*}}}*/

int main() {
    std::size_t n, q;
    std::cin >> n >> q;

    std::vector<int>a(n, (1ll << 31) - 1);
    splay_tree<min_monoid_t<int>> sp(a);

    while (q--) {
        int c;
        std::cin >> c;

        if (c==0) {
            std::size_t i;
            int x;
            std::cin >> i >> x;

            sp.set(i, x);
        }

        if (c==1) {
            std::size_t l, r;
            std::cin >> l >> r;
            r++;

            std::cout << sp.fold(l, r) << '\n';
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj-grl-2-a.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_A"

#line 2 "bbst/splay_tree.hpp"

#include <cstddef>
#include <cassert>
#include <utility>
#include <tuple>
#include <vector>
#include <memory>

// struct splay_node<Monoid>{{{
template <class Monoid>
struct splay_node {
    using this_type = splay_node<Monoid>;
    using value_type = typename Monoid::value_type;

    enum class kstate {
        left,
        right,
        none
    };

    this_type *parent, *left, *right;
    std::size_t size;
    value_type value;
    value_type acc;

    splay_node()
        : parent(nullptr)
        , left(nullptr)
        , right(nullptr)
        , size(1u)
        , value()
    {}

    splay_node(splay_node const&)=default;
    splay_node(splay_node&&)=default;
    splay_node& operator=(splay_node const&)=default;
    splay_node& operator=(splay_node&&)=default;
    ~splay_node()=default;

    splay_node(value_type x)
        : parent(nullptr)
        , left(nullptr)
        , right(nullptr)
        , size(1u)
        , value(x)
        , acc(x)
    {}

    kstate state() const {
        assert(!parent || parent->left==this || parent->right==this);
        if (!parent) return kstate::none;
        if (parent->left==this) return kstate::left;
        if (parent->right==this) return kstate::right;
        throw;
    }

    std::size_t lsize() const { return left ? left->size : 0u; }

    std::size_t rsize() const { return right ? right->size : 0u; }

    void update() {
        size = 1u;
        acc = value;
        if (left) {
            size += left->size;
            acc =  Monoid::op(acc, left->acc);
        }
        if (right) {
            size += right->size;
            acc =  Monoid::op(acc, right->acc);
        }
    }

    void set(value_type x) {
        value = x;
        update();
    }

    void rotate() {
        assert(parent);
        this_type *p=parent, *pp=p->parent, *c;

        this->parent=pp;
        if (pp) (pp->left==p ? pp->left : pp->right) = this;

        p->parent=this;

        if (p->left==this) {
            c = right;
            p->left=c;
            right=p;
            if(c)c->parent=p;
        }
        if (p->right==this) {
            c = left;
            p->right=c;
            left=p;
            if(c)c->parent=p;
        }

        p->update();
        update();
    }

    this_type* splay() {
        this_type *now = this;

        while (now->parent) {
            if (!now->parent->parent) {
                now->rotate();
            } else if (now->state() == now->parent->state()) {
                now->parent->rotate();
                now->rotate();
            } else {
                now->rotate();
                now->rotate();
            }
        }

        return now;
    }

    this_type* get(std::size_t i) {
        assert(i < size);
        if (i == lsize()) {
            splay();
            return this;
        } else if (i < lsize()) {
            assert(left);
            return left->get(i);
        } else {
            assert(right);
            return right->get(i-lsize()-1);
        }
    }

    template <class F> std::size_t
    partition_point(F&& f)
    {
        if (f(*this)) {
            return right
                ? size - right->size + right->partition_point(std::forward<F&&>(f))
                : size;
        } else {
            return left
                ? left->partition_point(std::forward<F&&>(f))
                : 0u;
        }
    }

    static this_type*
    merge(this_type* l, this_type* r)
    {
        if (!l) return r;
        if (!r) return l;
        l->parent = r;
        r->left = l;
        r->update();
        return r;
    }

    static this_type*
    merge_from_three(this_type* l, this_type* c, this_type* r)
    {
        l = merge(l, c);
        return merge(l, r);
    }

    static std::pair<this_type*, this_type*>
    split(this_type* root, std::size_t i)
    {
        assert(i <= root->size);
        if (i==0u) return std::make_pair(nullptr, root);
        if (i==root->size) return std::make_pair(root, nullptr);
        root = root->get(i);
        this_type* l = root->left;
        if(l) l->parent = nullptr;
        root->left = nullptr;
        root->update();
        return std::make_pair(l, root);
    }

    static std::tuple<this_type*, this_type*, this_type*>
    split_into_three(this_type* root, std::size_t l, std::size_t r)
    {
        assert(0 <= l && l <= r && r <= root->size);
        this_type *ltree, *ctree, *lctree, *rtree;
        std::tie(lctree, rtree) = split(root, r);
        std::tie(ltree, ctree) = split(lctree, l);
        return std::make_tuple( ltree, ctree, rtree );
    }

    std::pair<value_type, this_type*>
    fold(std::size_t l, std::size_t r)
    {
        assert(0 <= l && l <= r && r <= size);
        if (l==r) return std::make_pair(Monoid::id(), this);

        this_type *lt, *ct, *rt;
        std::tie(lt, ct, rt) = this_type::split_into_three(this, l, r);

        assert(ct);
        value_type folded = ct->acc;

        this_type* root = this_type::merge_from_three(lt, ct, rt);

        return std::make_pair(folded, root);
    }

    std::vector<value_type>
    to_vec() const
    {
        return to_vec_with([](this_type x){ return x.value; });
    }

    template <class F, class T = std::result_of_t<F(this_type)>> std::vector<T>
    to_vec_with(F const& f) const
    {
        std::vector<T> ans;
        if (left) {
            auto lvec = left->to_vec();
            ans.insert(ans.end(), lvec.begin(), lvec.end());
        }
        ans.push_back(f(*this));
        if (right) {
            auto rvec = right->to_vec();
            ans.insert(ans.end(), rvec.begin(), rvec.end());
        }
        return ans;
    }
};
/*}}}*/
// class splay_tree<Monoid>{{{
template <class Monoid>
class splay_tree {
    using node_type = splay_node<Monoid>;
    using value_type = typename Monoid::value_type;

    std::vector<std::unique_ptr<node_type>> node;
    std::size_t root_idx;

public:
    splay_tree()=default;
    splay_tree(splay_tree const&)=delete;
    splay_tree(splay_tree&&)=default;
    splay_tree& operator=(splay_tree const&)=delete;
    splay_tree& operator=(splay_tree&&)=default;
    ~splay_tree()=default;

    splay_tree(std::size_t n)
        : node(n)
    {
        for (auto&& p : node) {
            p = std::make_unique<node_type>(Monoid::id());
        }
        for (std::size_t i=0; i<n-1; i++) {
            node_type::merge(node.at(i).get(), node.at(i+1).get());
        }
        root_idx = n-1;
    }

    splay_tree(std::vector<value_type> const& a)
        : splay_tree(a.size())
    {
        for (std::size_t i=0; i<a.size(); i++) {
            node.at(i) = std::make_unique<node_type>(a.at(i));
        }
        for (std::size_t i=0; i<a.size()-1; i++) {
            node_type::merge(node.at(i).get(), node.at(i+1).get());
        }
        root_idx = a.size()-1;
    }

    bool empty() const { return node.empty(); }

    value_type get(std::size_t i)
    {
        assert(0 <= i && i < node.size());
        node_type* root = node.at(root_idx)->get(i);
        root_idx = root->lsize();
        return root->value;
    }

    void set(std::size_t i, value_type x)
    {
        assert(0 <= i && i < node.size());
        node_type* root = node.at(root_idx)->get(i);
        root->set(x);
        root_idx =  root->lsize();
    }

    value_type fold_all() const
    {
        return empty() ? Monoid::id() : node.at(root_idx)->acc;
    }

    value_type fold(std::size_t l, std::size_t r)
    {
        assert(0u <= l && l <= r && r <= node.size());
        if (empty()) {
            return Monoid::id();
        } else {
            value_type ret;
            node_type *root;
            std::tie(ret, root) = node.at(root_idx)->fold(l, r);
            root_idx = root->lsize();
            return ret;
        }
    }

    template <class F> std::size_t
    partition_point(F&& f) const
    {
        return empty()
            ? 0u
            :node.at(root_idx)->partition_point(std::forward<F&&>(f));
    }

    std::size_t lower_bound(value_type x) const
    {
        return partition_point([x](node_type n){ return n.value < x; });
    }

    std::size_t upper_bound(value_type x) const
    {
        return partition_point([x](node_type n){ return n.value <= x; });
    }

    template <class F, class T = std::result_of_t<F(node_type)>> std::vector<T>
    to_vec_with(F&& f) const
    {
        return empty()
            ? std::vector<T>{}
            : node.at(root_idx)->to_vec_with(std::forward<F&&>(f));
    }

    std::vector<value_type> to_vec() const
    {
        return empty()
            ? std::vector<value_type>{}
            : node.at(root_idx)->to_vec();
    }
};
/*}}}*/
#line 4 "test/aoj-grl-2-a.test.cpp"

#include <iostream>
#line 8 "test/aoj-grl-2-a.test.cpp"
#include <limits>

// min-monoid{{{
template <class Value> struct min_monoid_t {
    using value_type = Value;
    static value_type op(value_type l, value_type r) { return std::min(l, r); }
    static const value_type id() { return std::numeric_limits<value_type>::max(); }
};
/*}}}*/

int main() {
    std::size_t n, q;
    std::cin >> n >> q;

    std::vector<int>a(n, (1ll << 31) - 1);
    splay_tree<min_monoid_t<int>> sp(a);

    while (q--) {
        int c;
        std::cin >> c;

        if (c==0) {
            std::size_t i;
            int x;
            std::cin >> i >> x;

            sp.set(i, x);
        }

        if (c==1) {
            std::size_t l, r;
            std::cin >> l >> r;
            r++;

            std::cout << sp.fold(l, r) << '\n';
        }
    }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

