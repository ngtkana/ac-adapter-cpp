#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"

#include <cstddef>
#include <iostream>
#include <vector>

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

    std::size_t sz = tec.count;
    std::vector<std::vector<std::size_t>> mem(sz);
    for (std::size_t i=0; i<n; i++) {
        mem.at(tec.cmp.at(i)).push_back(i);
    }
    std::cout << sz << '\n';
    for (auto&& v : mem) {
        std::cout << v.size();
        for (std::size_t x : v) std::cout << ' ' << x;
        std::cout << '\n';
    }
}
