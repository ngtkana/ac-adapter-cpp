#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C"

#include "../tree/eular_tour_lca.hpp"

#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>


int main() {
    std::size_t n;
    std::cin >> n;
    std::vector<std::vector<std::size_t>> g(n);

    for (std::size_t i=0; i<n; i++) {
        std::size_t k;
        std::cin >> k;

        while (k--) {
            std::size_t j;
            std::cin >> j;
            g.at(i).push_back(j);
            g.at(j).push_back(i);
        }
    }

    eular_tour_lca lca(g);

    std::size_t q;
    std::cin >> q;

    while (q--) {
        std::size_t u, v;
        std::cin >> u >> v;

        std::cout << lca.get_lca(u, v) << '\n';
    }
}
