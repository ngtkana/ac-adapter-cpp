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
