#pragma once

#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>
#include <tuple>
#include <algorithm>

#include "../../others/cstdint2.hpp"
#include "../../others/vec.hpp"

/*
 * @title 2-辺連結成分分解 (Two-edges components)
 * @see [Wikipedia k-edge-connected graph](https://en.wikipedia.org/wiki/K-edge-connected_graph)
 * @docs graph/connectivity/tec_component.md
 */

class tec_component {
    bool built;

    // 1 回目の DFS
    // 計算するもの: ord, low, bridges
    // precondition: ckd = 0
    // post-condition: ckd = 2
    void low_link_dfs(usize x, usize p, usize& t) {
        auto&& v = g.at(x);
        ord.at(x) = low.at(x) = t++;
        ckd.at(x) = 1;

        // 親への多重辺
        if (2u <= std::count(v.begin(), v.end(), p)) {
            if (low.at(x) > ord.at(p)) low.at(x) = ord.at(p);
        }

        for (usize y : v) {
            // 未訪問の場合です。
            if (ckd.at(y)==0u) {
                low_link_dfs(y, x, t);
                // 橋を見つけました。
                if (ord.at(x) < low.at(y)) {
                    bridges.emplace_back(std::min(x, y), std::max(x, y));
                } else {
                    if (low.at(x) > low.at(y)) low.at(x) = low.at(y);
                }
            // 後退辺です。
            } else if (y!=p && ckd.at(y)==1u) {
                if (low.at(x) > ord.at(y)) low.at(x) = ord.at(y);
            }
        }
        ckd.at(x) = 2;
    }

    // 2 回目の DFS
    // 計算するも: cmp
    // precondition: cmp = size()
    // post-condition: cmp が計算済み
    void cmp_dfs(usize x) {
        for (usize y : g.at(x)) if (cmp.at(y)==size()) {
            cmp.at(y) = ord.at(x)<low.at(y)? ++count : cmp.at(x);
            cmp_dfs(y);
        }
    }

public:
    vec<vec<usize>> g;
    vec<usize> ord, low, ckd, cmp;

    vec<std::pair<usize, usize>> bridges;

    usize count;

    tec_component()=default;
    tec_component(tec_component const&)=default;
    tec_component(tec_component&&)=default;
    tec_component& operator=(tec_component const&)=default;
    tec_component& operator=(tec_component&&)=default;
    ~tec_component()=default;

    tec_component(vec<vec<usize>> const& g_)
        : tec_component(g_.size())
    {
        g = g_;
    }

    tec_component(usize n)
        : built(false), g(n), ord(n), low(n), ckd(n), cmp(n, n), count(0)
    {}

    void insert(usize i, usize j) {
        assert(usize{ 0 } <= i && i < size());
        assert(usize{ 0 } <= j && j < size());
        g.at(i).push_back(j);
        g.at(j).push_back(i);
    }


    usize size() const { return g.size(); }

    void build() {
        assert(built == false);
        built = true;

        for (usize i=0, t=0; i<size(); i++) if (ckd.at(i)==0) {
            low_link_dfs(i, 0, t);
        }

        assert(std::all_of(std::begin(ckd), std::end(ckd), [](usize x){ return x==2; }));

        for (usize i=0; i<size(); i++) if (cmp.at(i)==size()) {
            cmp.at(i) = count;
            cmp_dfs(i);
            count++;
        }
    }

    vec<vec<usize>> quotient_graph() {
        if (!built) build();
        vec<vec<usize>> h(count);

        for (auto&& e: bridges) {
            usize u, v;
            std::tie(u, v) = e;
            u = cmp.at(u);
            v = cmp.at(v);

            h.at(u).push_back(v);
            h.at(v).push_back(u);
        }
        return h;
    }
};
