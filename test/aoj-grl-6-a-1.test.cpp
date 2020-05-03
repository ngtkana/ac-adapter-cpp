#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A"

#include "../graph/flow/dinic.hpp"

#include <iostream>

int main() {
    int n, m;
    std::cin >> n >> m;

    auto ff=dinic<int>(n, 0, n-1);

    while(m--){
        int u, v, c;
        std::cin >> u >> v >> c;

        ff.insert(u, v, c);
    }

    std::cout<<ff.run()<<'\n';
}
