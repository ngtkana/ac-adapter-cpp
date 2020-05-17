/*
 * @title 木の直径 (Diameer of tree)
 * @docs graph/tree/tree_diameter.md
 */

#pragma once

#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_A"

#include <cassert>
#include <cstddef>
#include <utility>
#include <algorithm>
#include <vector>
#include <limits>

#include "../../others/cstdint2.hpp"
#include "../../others/vec.hpp"

struct no_weight;

template <class Weight>
struct tree_diameter_adapter {
    using weight_type = Weight;
    using edge_type = std::pair<usize, weight_type>;
    static usize to(edge_type const& e) { return e.first; }
    static weight_type weight(edge_type const& e) { return e.second; }
};

template <>
struct tree_diameter_adapter<no_weight> {
    using weight_type = usize;
    using edge_type = usize;
    static usize to(edge_type e) { return e; }
    static weight_type weight(edge_type) { return 1; }
};

template <class> class tree_diameter;

template <class Weight=no_weight>
class tree_diameter {
    using adapter_type = tree_diameter_adapter<Weight>;
    using edge_type = typename adapter_type::edge_type;
    using weight_type = typename adapter_type::weight_type;

    bool built = false;

    weight_type inf() { return std::numeric_limits<weight_type>::max(); }

public:
    vec<vec<edge_type>> g;
    vec<weight_type> dist;
    usize s, t;

    tree_diameter()=default;
    tree_diameter(tree_diameter const&)=default;
    tree_diameter(tree_diameter&&)=default;
    tree_diameter& operator=(tree_diameter const&)=default;
    tree_diameter& operator=(tree_diameter&&)=default;
    ~tree_diameter()=default;

    tree_diameter(usize n)
        : g(n), dist(n) {}

    // FIXME: 実装の注入で書き直せそうです。
    void insert_with_weight(usize u, usize v, Weight w) {
        assert(u < size());
        assert(v < size());
        g.at(u).emplace_back(v, w);
        g.at(v).emplace_back(u, w);
    }

    // FIXME: 実装の注入で書き直せそうです。
    void insert_without_weight(usize u, usize v) {
        assert(u < size());
        assert(v < size());
        g.at(u).push_back(v);
        g.at(v).push_back(u);
    }

    tree_diameter(vec<vec<edge_type>> const& g_)
        : g(g_), dist(g_.size())
    {
        build();
    }

    usize size() const { return g.size(); }

    void build(usize s_ = 0) {
        assert(!built);
        built = true;
        s = s_;

        for (usize i=0; i<2; i++) {
            dist.assign(size(), inf());
            dist.at(s) = 0;
            vec<usize> que = {s};

            for (usize j=0; j<que.size(); j++) {
                usize x = que.at(j);
                for (auto&& e: g.at(x)) if (dist.at(adapter_type::to(e))==inf()) {
                    dist.at(adapter_type::to(e)) = dist.at(x) + adapter_type::weight(e);
                    que.push_back(adapter_type::to(e));
                }
            }
            t = std::max_element(dist.begin(), dist.end()) - dist.begin();
            std::swap(s, t);
        }
    }

    weight_type len() {
        if (!built) build();
        assert(dist.at(t)==0 && dist.at(s)!=inf());
        return dist.at(s);
    }

    std::pair<usize, usize> extremals()  {
        if (!built) build();
        assert(dist.at(t)==0 && dist.at(s)!=inf());
        return std::make_pair(s, t);
    }

    vec<usize> verticies() {
        if (!built) build();
         vec<usize> ans = {s};
         while (ans.back()!=t) {
             auto&& v = g.at(ans.back());

             usize y =
                 adapter_type::to(*std::find_if(
                     v.begin(),
                     v.end(),
                     [this, dx=dist.at(ans.back())](usize y_){
                         return dist.at(y_) == dx - 1;
                     }
                 ));

             ans.push_back(y);
         }
         assert(ans.size()==len()+1);
         assert([&]{
             for (usize i=0; i<=len(); i++) {
                 assert(i==dist.at(ans.at(i)));
             }
             return true;
         }());
         return ans;
    }
};

