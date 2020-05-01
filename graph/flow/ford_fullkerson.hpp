#pragma once

#include <bits/stdc++.h>

template <class Flow> struct flow_edge {
    std::size_t to;
    std::size_t rev;
    Flow cap;

    // special member functions
    flow_edge()=default;
    flow_edge(const flow_edge&)=default;
    flow_edge(flow_edge&&)=default;
    flow_edge&operator=(const flow_edge&)=default;
    flow_edge&operator=(flow_edge&&)=default;
    ~flow_edge()=default;

    flow_edge(std::size_t to_, std::size_t rev_, Flow cap_)
        : to(to_), rev(rev_), cap(cap_) {}
};

template <class Flow> std::ostream& operator<<(std::ostream& os, flow_edge<Flow> e) {
    return os << "(" << e.to << "," << e.cap << ")";
}

template <class Flow> class ford_fullkerson {
    std::size_t s, t;
    int time;
    std::vector<std::vector<flow_edge<Flow>>> g;
    std::vector<int> ckd;

    Flow run_impl(std::size_t x, Flow d /* フローが来ました */) {
        ckd.at(x) = time;

        if (x == t) {
            return d;
        }

        for (auto&& e : g.at(x)) {
            if (ckd.at(e.to) == time || e.cap == zero()) {
                continue;
            }

            Flow ret = run_impl(e.to, std::min(d, e.cap) /* 次に送ります */); // 帰ってきました

            if (ret == zero()) {
                continue;
            }

            e.cap -= ret;
            g.at(e.to).at(e.rev).cap += ret;

            return ret; // さらに返します
        }
        return zero();
    }

public:

    // special member functions
    ford_fullkerson()=default;
    ford_fullkerson(const ford_fullkerson&)=default;
    ford_fullkerson(ford_fullkerson&&)=default;
    ford_fullkerson&operator=(const ford_fullkerson&)=default;
    ford_fullkerson&operator=(ford_fullkerson&&)=default;
    ~ford_fullkerson()=default;

    ford_fullkerson(std::size_t n, std::size_t s_, int t_)
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
            f = run_impl(s, inf());
            if (f == zero()) break;
            if (f == inf()) return inf(); // 容量無限の辺があるケースに対応です。
            flow += f;
        }

        return flow;
    }
};

