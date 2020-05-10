#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_3_B"

#include <cstddef>
#include <iostream>
#include <utility>
#include <tuple>
#include <vector>
#include <algorithm>

#include "../graph/connectivity/tec_component.hpp"

int main(){
    std::size_t n, m;
    std::cin >> n >> m;
    tec_component tec(n);

    while (m--) {
        std::size_t u, v;
        std::cin >> u >> v;
        tec.insert(u, v);
    }
    tec.build();

    std::vector<std::pair<std::size_t, std::size_t>> bridges = tec.bridges;
    std::sort(bridges.begin(), bridges.end());

    for (auto&& e : bridges) {
        std::size_t i, j;
        std::tie(i, j) = e;
        std::cout << i << ' ' << j << '\n';
    }
}
