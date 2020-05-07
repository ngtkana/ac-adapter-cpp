#pragma once

#include <cstddef>
#include <cassert>
#include <utility>
#include <tuple>
#include <vector>

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
    partition_point(F const& f)
    {
        if (f(this)) {
            return left ? partition_point(left, f) : 0u;
        } else {
            return right ? size - right->size + partition_point(right, f) : size;
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
        if (l==r) return std::make_pair(Monoid::id, this);

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
