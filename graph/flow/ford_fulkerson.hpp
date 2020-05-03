#pragma once

#include <vector>
#include <cstddef>
#include <algorithm>

#include "flow_edge.hpp"

template <class Flow> class ford_fulkerson {
    std::size_t s, t;
    int time;
    std::vector<std::vector<flow_edge<Flow>>> g;
    std::vector<int> ckd;

    // 増分路を探します。
    Flow find_aug(std::size_t x, Flow d /* フローが来ました */) {
        ckd.at(x) = time;
        if (x == t) return d;

        for (auto&& e : g.at(x)) if (ckd.at(e.to)!=time && e.cap!=zero()) {
            Flow ret = find_aug(e.to, std::min(d, e.cap) /* 次に送ります */); // 帰ってきました
            if (ret==zero())continue;

            e.cap -= ret;
            g.at(e.to).at(e.rev).cap += ret;
            return ret; // さらに返します
        }
        return zero();
    }

public:
    // special member functions
    ford_fulkerson()=default;
    ford_fulkerson(const ford_fulkerson&)=default;
    ford_fulkerson(ford_fulkerson&&)=default;
    ford_fulkerson&operator=(const ford_fulkerson&)=default;
    ford_fulkerson&operator=(ford_fulkerson&&)=default;
    ~ford_fulkerson()=default;

    ford_fulkerson(std::size_t n, std::size_t s_, int t_)
        : s(s_), t(t_), time(0), g(n), ckd(n, -1) {}

    std::size_t size() const noexcept { return g.size(); }

    Flow inf() const { return std::numeric_limits<Flow>::max(); }

    Flow zero() const { return Flow{ 0 }; }

    void insert(std::size_t u, std::size_t v, Flow w) {
        std::size_t su = g.at(u).size();
        std::size_t sv = g.at(v).size();

        g.at(u).emplace_back(v, sv, w);
        g.at(v).emplace_back(u, su, zero());
    }

    Flow run() {
        Flow flow = zero();

        for(Flow f; ; time++) {
            f = find_aug(s, inf());
            if (f == zero()) break;
            if (f == inf()) return inf(); // 容量無限の辺があるケースに対応です。
            flow += f;
        }

        return flow;
    }
};

/*
 * @title Ford−Fulkerson
 * @category graph
 * @category flow
 * @brief 計算量は $ O ( E f ) $ です。
 * @see https://en.wikipedia.org/wiki/Ford%E2%80%93Fulkerson_algorithm
 */
