#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_1_A"

#include <cstddef>
#include <cassert>
#include <iostream>
#include <vector>
#include <limits>

#include "../graph/edge.hpp"
#include "../graph/shortest_path/dijkstra.hpp"

int main() {
    std::size_t n, m, s;
    std::cin >> n >> m >> s;

    std::vector<std::vector<edge<int>>> g(n);
    int inf = std::numeric_limits<int>::max();
    while (m--) {
        std::size_t u, v;
        int w;
        std::cin >> u >> v >> w;

        g.at(u).emplace_back(v, w);
    }

    std::vector<int> dist = dijkstra(g, s);

    for (int d : dist) {
        std::cout << (d==inf ? "INF" : std::to_string(d)) << '\n';
    }
}
