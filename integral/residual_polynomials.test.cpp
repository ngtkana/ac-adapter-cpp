#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <type_traits>

#include "../others/vec.hpp"
#include "../others/cstdint2.hpp"
#include "mint.hpp"
#include "residual_polynomials.hpp"

using mint = modint<std::integral_constant<i64, 1'000'000'007>>;

int main() {
    vec<mint> f{2, 3, 4};
    resudual_polynomials<mint> rp(f);

    u32 a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
