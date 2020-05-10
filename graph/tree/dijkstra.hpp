#pragma once

#include <utility>
#include <tuple>
#include <vector>
#include <queue>
#include <limits>

#include "edge.hpp"

template <class Weight> std::vector<Weight>
dijkstra(std::vector<std::vector<edge<Weight>>> const& g, std::size_t s)
{
    assert(0 <= s && s < g.size());
    Weight inf = std::numeric_limits<Weight>::max();
    std::vector<Weight> dist(g.size(), inf);
    std::priority_queue<std::pair<Weight, std::size_t>> que;

    dist.at(s) = 0;
    que.emplace(0, s);
    while (!que.empty()) {
        std::size_t x;
        Weight dx;
        std::tie(dx, x) = que.top(); que.pop();
        dx = -dx;

        if (dist.at(x) < dx) continue;

        for (auto&& e : g.at(x)) {
            std::size_t y = e.to;
            Weight dy = dx + e.weight;

            if (dist.at(y) <= dy) continue;
            dist.at(y) = dy;
            que.emplace(-dy, y);
        }
    }

    return dist;
}
