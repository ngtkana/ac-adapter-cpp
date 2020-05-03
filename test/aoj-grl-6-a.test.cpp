#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A"

#include "../graph/flow/ford_fulkerson.hpp"

#include <iostream>

int main(){
    int n, m;
    std::cin >> n >> m;

    auto ff=ford_fulkerson<int>(n, 0, n-1);

    while(m--){
        int u, v, c;
        std::cin >> u >> v >> c;

        ff.insert(u, v, c);
    }

    std::cout<<ff.run()<<'\n';
}
