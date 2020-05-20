#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../integral/nt_trsf.hpp"

#include <iostream>
#include <cassert>

using mint = modint<std::integral_constant<i32, 998244353>>;

int main(){
    nt_trsf<mint> ntt;

    std::size_t n, m;
    std::cin >> n >> m;

    std::vector<mint> a(n), b(m);
    for (mint& x: a) std::cin >> x;
    for (mint& x: b) std::cin >> x;

    auto c = ntt.multiply(a, b);
    c.resize(n+m-1);

    for (std::size_t i=0; i<c.size(); i++) {
        std::cout << (i?" ":"") << c.at(i);
    }
    std::cout << '\n';
}
