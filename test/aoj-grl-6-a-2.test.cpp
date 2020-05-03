#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A"

#include "../graph/flow/relabel_to_front.hpp"

#include <iostream>

int main() {
    int n, m;
    std::cin >> n >> m;

    auto rf=relabel_to_front<int>(n, 0, n-1);

    while(m--){
        int u, v, c;
        std::cin >> u >> v >> c;

        rf.insert(u, v, c);
    }

    std::cout<<rf.run()<<'\n';
}
