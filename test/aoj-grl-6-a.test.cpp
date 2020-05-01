#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A"

#include "../graph/flow/ford_fullkerson.hpp"

#include <iostream>

int main(){
    int n, m;
    std::cin >> n >> m;

    auto ff=ford_fullkerson<int>(n, 0, n-1);

    while(m--){
        int u, v, c;
        std::cin >> u >> v >> c;

        ff.insert(u, v, c);
    }

    std::cout<<ff.run()<<'\n';
}

/*
 * @title Ford−Fulkerson
 * @category graph
 * @category flow
 * @brief 計算量は $ O ( E f ) $ です。
 * @see https://ja.wikipedia.org/wiki/%E3%83%95%E3%82%A9%E3%83%BC%E3%83%89%E3%83%BB%E3%83%95%E3%82%A1%E3%83%AB%E3%82%AB%E3%83%BC%E3%82%BD%E3%83%B3%E3%81%AE%E3%82%A2%E3%83%AB%E3%82%B4%E3%83%AA%E3%82%BA%E3%83%A0
 */
