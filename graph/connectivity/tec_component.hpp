#pragma once

#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>
#include <algorithm>

class tec_component
{
public:
    std::vector<std::vector<std::size_t>> g;
    std::vector<std::size_t> ord, low, ckd, cmp;

    std::vector<std::vector<std::size_t>> bfree_graph;
    std::vector<std::pair<std::size_t, std::size_t>> bridges;

    std::size_t count;

private:
    void tec_internal_cmn(std::size_t& i, std::size_t j) { if (i>j) i=j; }

    void found_bridge(std::size_t i, std::size_t j) {
        if (i>j) std::swap(i, j);
        bridges.emplace_back(i, j);
    }

    void found_non_bridge(std::size_t i, std::size_t j) {
        bfree_graph.at(i).push_back(j);
        bfree_graph.at(j).push_back(i);
    }

    void dfs(std::size_t x, std::size_t p, std::size_t t) {
        auto&& v = g.at(x);
        ord.at(x) = low.at(x) = t;
        ckd.at(x) = 1;

        // 自己ループは後退辺扱いです。
        if (std::find(v.begin(), v.end(), x) != v.end()) {
            found_non_bridge(x, x);
        }

        // 親は 2 人いる場合のみ後退辺扱いです。
        if (2u <= std::count(v.begin(), v.end(), p)) {
            tec_internal_cmn(low.at(x), ord.at(p));
            found_non_bridge(x, p);
        }

        for (std::size_t y : v) {
            // 未訪問の場合です。
            if (ckd.at(y)==0u) {
                dfs(y, x, t+1);
                // 橋を見つけました。
                if (ord.at(x) < low.at(y)) {
                    found_bridge(x, y);
                // 橋でないものを見つけました。
                } else {
                    tec_internal_cmn(low.at(x), low.at(y));
                    found_non_bridge(x, y);
                }

            // 後退辺です。
            } else if (y!=p && ckd.at(y)==1u) {
                tec_internal_cmn(low.at(x), ord.at(y));
                // 後退辺は橋ではありません。
                found_non_bridge(x, y);
            }
        }
        ckd.at(x) = 2;
    }

    void efs(std::size_t x) {
        ckd.at(x) = 3u;
        for (std::size_t y : bfree_graph.at(x)) {
            if (ckd.at(y)==3u) continue;
            cmp.at(y) = cmp.at(x);
            efs(y);
        }
    }

public:
    tec_component()=default;
    tec_component(tec_component const&)=default;
    tec_component(tec_component&&)=default;
    tec_component& operator=(tec_component const&)=default;
    tec_component& operator=(tec_component&&)=default;
    ~tec_component()=default;

    tec_component(std::size_t n)
        : g(n), ord(n), low(n), ckd(n), cmp(n), bfree_graph(n), count(0)
    {}

    std::size_t size() const { return g.size(); }

    void insert(std::size_t i, std::size_t j) {
        assert(std::size_t{ 0 } <= i && i < size());
        assert(std::size_t{ 0 } <= j && j < size());
        g.at(i).push_back(j);
        g.at(j).push_back(i);
    }

    void build() {
        assert(size());

        for (std::size_t i=0; i<size(); i++) {
            dfs(i, 0, 0);
        }

        assert(std::all_of(std::begin(ckd), std::end(ckd), [](std::size_t x){ return x==2; }));

        for (std::size_t i=0; i<size(); i++) {
            if (ckd.at(i)==3u) continue;
            cmp.at(i) = count++;
            efs(i);
        }
    }
};

/*
 * @title 2-辺連結成分分解 (Two-edges components)
 * @see [Wikipedia k-edge-connected graph](https://en.wikipedia.org/wiki/K-edge-connected_graph)
 * @docs graph/connectivity/tec_component.md
 */
