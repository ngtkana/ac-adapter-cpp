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


# :heavy_check_mark: スプレー木 (Splay tree)

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d342894e126a2cdd0812cd3a6c903bbd">bbst</a>
* <a href="{{ site.github.repository_url }}/blob/master/bbst/splay_tree.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-12 20:29:34+09:00




## 構造体 $ \mathtt { splay \unicode { 95 } node } $ 

### 構築

- $ \mathtt { splay \unicode { 95 } node() } $ : ポインタをすべて $ \mathtt { nullptr } $ で初期化し、サイズを $ 1 $ にし、値をデフォルト構築します。

- $ \mathtt { splay \unicode { 95 } node(x) } $ : ポインタをすべて $ \mathtt { nullptr } $ で初期化し、サイズを $ 1 $ にし、値を $ x $ で初期化します。


### オブザーバー

- $ \mathtt { state() } $ : 自分が何者であるのかを知らしめます。

- $ \mathtt { lsize() } $ : 左の子のサイズを返します。いない場合は $ 0 $ です。

- $ \mathtt { rsize() } $ : 右の子のサイズを返します。いない場合は $ 0 $ です。

- $ \mathtt { partition \unicode { 95 } point ( root, f )  } $ : 述語 $ f : \mathtt{ splay \unicode {95} node } \rightarrow \mathtt{ bool } $ を受け取り、 $ [ 0, i [ $ で $ \mathtt{ true } $ 、 $ [ i, \mathtt{ size } [ $ で $ \mathtt{ false } $ となるような $ i $ を返します。ただし区分化されている必要があります。

- $ \mathtt { to \unicode {95} vec() } $ : 値を順番に $ \mathtt { vector } $ に入れて返します。

- $ \mathtt { to \unicode {95} vec \unicode {95} with (f) } $ : 関数 $ f: \mathtt{ splay \unicode { 95 } node } \rightarrow T $ で射影した結果を $ \mathtt{ vector } $ に入れて返します。


### 更新

- $ \mathtt { update() } $ : $ \mathtt{ size } $ と $ \mathtt{ acc } $ を更新です。子の情報が正しいとき、私の情報も正しくなります。

- $ \mathtt { set(x) } $ : 自分の値を $ x $ にセットし、 $ \mathtt{ update() } $ を呼びます。


### 変形ロボとしての基本動作

- $ \mathtt { rotate() } $ : 回転をして、自分を一つ上に挙げます。親がいない場合は実行時エラーです。操作の終了語、親、自分の $ \mathtt { update() } $ が呼ばれます。

- $ \mathtt { splay() } $ : 自分が根になるまで、自分や親の $ \mathtt { rotate() } $ を呼び続けます。


### 平衡順序木の操作

- $ \mathtt { get(i) } $ : 自分の部分木のうち、ひだりから $ i $ 番目のものを探して根まで持っていき、それへのポインターを返します。

- $ \mathtt { partition \unicode { 95 } point ( f ) } $ : 述語 $ f : \mathtt{ splay \unicode {95} node } \rightarrow \mathtt{ bool } $ を受け取り、 $ [ 0, i [ $ で $ \mathtt{ true } $ 、 $ [ i, \mathtt{ size } [ $ で $ \mathtt{ false } $ となるような $ i $ を返します。ただし区分化されている必要があります。

- $ \mathtt { merge(l, r) } $ : $ r $ の左下に $ l $ をつけます。

- $ \mathtt { merge \unicode { 95 } from \unicode { 95 } three (l, c, r) } $ : $ r $ の左下に $ c $ 、その左下に $ l $ をつけます。

- $ \mathtt { split(i) } $ : 自分の部分木を、左側 $ i $ 個、右側 $ \mathtt{ size } - i $ 個に分けます。どちらかが $ 0 $ 個になる場合は、そちらは $ \mathtt{ nullptr } $ です。また $ \mathtt{ size } $ よりも大きな $ i $ を指定すると、実行時エラーです。

- $ \mathtt { split \unicode { 95 } into \unicode { 95 } three (l, r) } $ : 同様に、 $ l $ 個、 $ r - l $ 個、 $ \mathtt{ size } - r $ 個に分けます。


### 値の集約

- $ \mathtt { fold(l, r) } $ : 自分の部分木の中で $ [l, r[ $ に対応する添字部分の値を集約します。添字がおかしいときには実行時エラーです。


## 構造体 $ \mathtt { splay \unicode { 95 } tree } $ 

中身は $ \mathtt { unique \unicode { 95 } ptr } $ の $ \mathtt {vector} $ と、根の添字番号です。空のときには根は $ -1 $ ( = `std::numeric_limits<std::size_t>::max()`) になっています。

### 構築

- $ \mathtt { splay \unicode { 95 } tree () } $ : 引数 $ \mathtt { 0 } $ で下記のコンストラクタに移譲します。

- $ \mathtt { splay \unicode { 95 } tree (n) } $ : $ n $ 個のノードが左下から右上に向かって一直線になったスプレー木を構築します。ノードはデフォルト構築されたあと、 $ \mathtt { merge } $ が呼ばれます。

- $ \mathtt { splay \unicode { 95 } tree (a) } $ : 値の入った $ \mathtt {vector} $ を受け取り、スプレー木を構築します。


### オブザーバー（ $ \mathtt{ const } $ がついているとは限りません。）

- $ \mathtt{ empty() } $ : 空ならば $ \mathtt { true } $ です。

- $ \mathtt{ size() } $ : サイズを返します。

- $ \mathtt{ get(i) } $ : $ i $ 番目の値を返します。

- $ \mathtt{ fold \unicode {95} all() } $ : すべてを畳み込んだ値を返します。空ならば $ \mathtt { id } $ ですし、空でなければ根の $ \mathtt { acc } $ です。

- $ \mathtt{ fold(l, r) } $ : 区間 $ [l, r[ $ を畳み込んだ値を返します。

- $ \mathtt{ partion \unicode { 95 } point (f) } $ : 空ならば $ 0 $ です。空でなければ根の同名のメンバ関数を呼びます。

- $ \mathtt{ lower \unicode { 95 } bound (x, cmp=less) } $ : ソート済みであるとして、値が $ x $ 以上の最も左の添字を返します。存在しない場合は $ \mathtt{ size } $ を返します。内部では $ \mathtt { partition \unicode {95} point } $ に転送をしています。

- $ \mathtt{ upper \unicode { 95 } bound (x, cmp=less) } $ : ソート済みであるとして、値が $ x $ を超える最も左の添字を返します。存在しない場合は $ \mathtt{ size } $ を返します。内部では $ \mathtt { partition \unicode {95} point } $ に転送をしています。

- $ \mathtt{ to \unicode {95} vec() } $ : 値を $ \mathtt{ vector } $ にコレクトします。

- $ \mathtt{ to \unicode {95} vec \unicode {95 } with(f) } $ : 関数 $ f: \mathtt{ splay \unicode {95} node } \rightarrow T $ で射影した結果を $ \mathtt { vector } $ にコレクトです。


### 値の更新

- $ \mathtt{ set(i, x) } $ : $ i $ 番目の値を $ x $ にセットします。

- $ \mathtt{ add(i, x) } $ : $ i $ 番目の値を $ \mathtt{get}(i) + x $ にセットします。

- $ \mathtt{ sub(i, x) } $ : $ i $ 番目の値を $ \mathtt{get}(i) - x $ にセットします。

- $ \mathtt{ mul(i, x) } $ : $ i $ 番目の値を $ \mathtt{get}(i) * x $ にセットします。

- $ \mathtt{ div(i, x) } $ : $ i $ 番目の値を $ \mathtt{get}(i) / x $ にセットします。

- $ \mathtt{ map(i, f) } $ : $ i $ 番目の値を $ f(\mathtt{get}(i)) $ にセットします。


### ノードの挿入と削除

すべての挿入操作は、メモリプールに新しいノードを $ \mathtt { push \unicode { 95 } back } $ し、$ \mathtt { size \unicode { 95 } } $ を $ 1 $ 増加させます。

すべての削除操作は、ノードを削除せず、$ \mathtt { size \unicode { 95 } } $ を $ 1 $ 減少させます。

- $ \mathtt{ push \unicode { 95 } front( x ) } $ : 木の最も左に値 $ x $ を持つノードを追加します。

- $ \mathtt{ push \unicode { 95 } back( x ) } $ : 木の最も右に値 $ x $ を持つノードを追加します。

- $ \mathtt{ insert( i,  x ) } $ : 木の$ i $番目の位置に値 $ x $ を持つノードを追加します。

- $ \mathtt{ pop \unicode { 95 } front() } $ : 木の最も左のノードを削除します。木が空のときには実行時エラーです。

- $ \mathtt{ pop \unicode { 95 } back() } $ : 木の最も右のノードを削除します。木が空のときには実行時エラーです。

- $ \mathtt{ erase( i ) } $ : 木の $ i $ 番目の位置のノードを削除します。範囲外のときには実行時エラーです。


### 困りました。

$ \mathtt { splice } $ はどう実装したらよいのでしょう。
$ \mathtt { vector } $ さんに管理していたけるのは大変嬉しいのですが、あの、ちょっと、そこのあなた、
勝手にデストラクタを呼ぶのをやめて頂けないとですね、私は答弁の方に集中できなくですね……


## Depends on

* :heavy_check_mark: <a href="../others/cstdint2.hpp.html">others/cstdint2.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj-alds1-4-b.test.cpp.html">test/aoj-alds1-4-b.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj-grl-2-a.test.cpp.html">test/aoj-grl-2-a.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj-grl-2-b.test.cpp.html">test/aoj-grl-2-b.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj-itp2-1-a.test.cpp.html">test/aoj-itp2-1-a.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj-itp2-1-b.test.cpp.html">test/aoj-itp2-1-b.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj-itp2-1-c.test.cpp.html">test/aoj-itp2-1-c.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/*
 * @title スプレー木 (Splay tree)
 * @docs bbst/splay_tree.md
 */

#pragma once

#include <cstddef>
#include <cassert>
#include <utility>
#include <tuple>
#include <vector>
#include <memory>

#include "../others/cstdint2.hpp"

template <class Monoid>
struct splay_node
{
    using this_type = splay_node<Monoid>;
    using value_type = typename Monoid::value_type;

    enum class kstate {
        left,
        right,
        none
    };

    this_type *parent, *left, *right;
    usize size;
    value_type value;
    value_type acc;

    splay_node()
        : parent(nullptr), left(nullptr), right(nullptr), size(1u), value(), acc() {}

    splay_node(splay_node const&)=default;
    splay_node(splay_node&&)=default;
    splay_node& operator=(splay_node const&)=default;
    splay_node& operator=(splay_node&&)=default;
    ~splay_node()=default;

    splay_node(value_type x)
        : parent(nullptr), left(nullptr), right(nullptr), size(1u), value(x), acc(x) {}

    kstate state() const {
        assert(!parent || parent->left==this || parent->right==this);
        if (!parent) return kstate::none;
        if (parent->left==this) return kstate::left;
        if (parent->right==this) return kstate::right;
        throw;
    }

    usize lsize() const { return left ? left->size : 0u; }
    usize rsize() const { return right ? right->size : 0u; }

    static std::vector<value_type>
    to_vec(this_type const* root) {
        return to_vec_with(root, [](this_type x){ return x.value; });
    }

    template <class F, class T = std::result_of_t<F(this_type)>>
    static std::vector<T>
    to_vec_with(this_type const* root, F&& f) {
        std::vector<T> ans;

        auto dfs = [&ans, &f](auto&&dfs_, this_type const* x) -> void {
            if (!x) return;
            dfs_(dfs_, x->left);
            ans.push_back(f(*x));
            dfs_(dfs_, x->right);
        };
        dfs(dfs, root);
        return ans;
    }

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

    this_type* get(usize i) {
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

    template <class F> static usize
    partition_point(this_type const* root, F&& f) {
        auto dfs = [&f](auto&& dfs_, this_type const* x) -> usize {
            if (!x) {
                return 0u;
            } else if (f(*x)) {
                return x->size - x->rsize() + dfs_(dfs_, x->right);
            } else {
                return dfs_(dfs_, x->left);
            }
        };
        return dfs(dfs, root);
    }

    static this_type*
    merge(this_type* l, this_type* r) {
        if (!l && !r) return nullptr;
        assert(l!=r);
        if (!l) return r;
        if (!r) return l;
        r = r->get(0u);
        l->parent = r;
        r->left = l;
        r->update();
        return r;
    }

    static this_type*
    merge_from_three(this_type* l, this_type* c, this_type* r) {
        l = merge(l, c);
        return merge(l, r);
    }

    static std::pair<this_type*, this_type*>
    split(this_type* root, usize i)
    {
        if (!root) {
            assert(i==0);
            return std::make_pair(nullptr, nullptr);
        }
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
    split_into_three(this_type* root, usize l, usize r)
    {
        assert(0 <= l && l <= r && r <= root->size);

        this_type *ltree, *ctree, *lctree, *rtree;
        std::tie(lctree, rtree) = split(root, r);
        std::tie(ltree, ctree) = split(lctree, l);
        return std::make_tuple( ltree, ctree, rtree );
    }

    std::pair<value_type, this_type*>
    fold(usize l, usize r)
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
};

template <class Monoid>
class splay_tree {
    using node_type = splay_node<Monoid>;
    using value_type = typename Monoid::value_type;

    std::vector<std::unique_ptr<node_type>> node;
    node_type* root;
    usize size_;

public:
    splay_tree()
        : splay_tree(0u) {}

    splay_tree(splay_tree const&)=delete;
    splay_tree(splay_tree&&)=default;
    splay_tree& operator=(splay_tree const&)=delete;
    splay_tree& operator=(splay_tree&&)=default;
    ~splay_tree()=default;

    splay_tree(usize n)
        : node(n), size_(n)
    {
        for (auto&& p : node) {
            p = std::make_unique<node_type>(Monoid::id());
        }
        for (usize i=1; i<n; i++) {
            node_type::merge(node.at(i-1).get(), node.at(i).get());
        }
        root = n==0
            ? nullptr
            : node.back().get()
            ;
    }

    splay_tree(std::vector<value_type> const& a)
        : splay_tree(a.size())
    {
        for (usize i=0; i<a.size(); i++) {
            node.at(i) = std::make_unique<node_type>(a.at(i));
        }
        for (usize i=0; i<a.size()-1; i++) {
            node_type::merge(node.at(i).get(), node.at(i+1).get());
        }
        root = empty()
            ? nullptr
            : node.back().get()
            ;
    }

    bool empty() const { return size()==0u; }

    usize size() const { return size_; }

    value_type get(usize i) {
        assert(0 <= i && i < node.size());
        root = root->get(i);
        return root->value;
    }

    value_type fold_all() const {
        return empty() ? Monoid::id() : root->acc;
    }

    value_type fold(usize l, usize r) {
        assert(0u <= l && l <= r && r <= node.size());
        if (empty()) {
            return Monoid::id();
        } else {
            value_type ret;
            std::tie(ret, root) = root->fold(l, r);
            return ret;
        }
    }

    template <class F> usize
    partition_point(F&& f) const {
        return node_type::partition_point(root, std::forward<F&&>(f));
    }

    template <class Cmp=std::less<value_type>>
    usize lower_bound(value_type x, Cmp&& cmp={}) const {
        return partition_point([x, &cmp](node_type n){ return cmp(n.value, x); });
    }

    template <class Cmp=std::less<value_type>>
    usize upper_bound(value_type x, Cmp&& cmp={}) const {
        return partition_point([x, &cmp](node_type n){ return cmp(x, n.value); });
    }

    template <class F, class T = std::result_of_t<F(node_type)>> std::vector<T>
    to_vec_with(F&& f) const {
        return node_type::to_vec_with(root, std::forward<F&&>(f));
    }

    std::vector<value_type> to_vec() const {
        return node_type::to_vec(root);
    }

    void set(usize i, value_type x) {
        assert(0 <= i && i < node.size());
        root = root->get(i);
        root->set(x);
    }

    void add(usize i, value_type x) { set(i, get(i) + x); }
    void sub(usize i, value_type x) { set(i, get(i) - x); }
    void mul(usize i, value_type x) { set(i, get(i) * x); }
    void div(usize i, value_type x) { set(i, get(i) / x); }

    template <class F>
    void map(usize i, F&& f) { set(i, f(get(i))); }

    void push_front(value_type x) {
        node.push_back(std::make_unique<node_type>(x));
        root = node_type::merge(node.back().get(), root);
        ++size_;
    }

    void push_back(value_type x) {
        node.push_back(std::make_unique<node_type>(x));
        root = node_type::merge(root, node.back().get());
        ++size_;
    }

    void insert(usize i, value_type x) {
        assert(i <= size());
        node_type *l, *r;
        std::tie(l, r) = node_type::split(root, i);
        node.push_back(std::make_unique<node_type>(x));
        root = node_type::merge_from_three(l, node.back().get(), r);
        size_++;
    }

    void pop_front() {
        assert(!empty());
        if (1u==size_) {
            node.clear();
            root = nullptr;
        } else {
            root = node_type::split(root, 1).second;
        }
        --size_;
    }

    void pop_back() {
        assert(!empty());
        if (1u==size_) {
            node.clear();
            root = nullptr;
        } else {
            root = node_type::split(root, size()-1).first;
        }
        --size_;
    }

    void erase(usize i) {
        assert(i < size());
        node_type *l, *r;
        std::tie(l, std::ignore, r) = node_type::split_into_three(root, i, i+1);
        root = node_type::merge(l, r);
        size_--;
    }
};

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
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 214, in update
    raise BundleError(path, i + 1, "#pragma once found in a non-first line")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: bbst/splay_tree.hpp: line 6: #pragma once found in a non-first line

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

