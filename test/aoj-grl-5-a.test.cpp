#include <cstddef>
#include <iostream>

#include "../graph/tree/tree_diameter.hpp"

int main() {
    usize n;
    std::cin >> n;

    tree_diameter<i64> td(n);
    for (usize i=0; i<n-1; i++) {
        usize u, v;
        i64 w;
        std::cin >> u >> v >> w;

        td.insert_with_weight(u, v, w);
    }

    std::cout << td.len() << '\n';
}
