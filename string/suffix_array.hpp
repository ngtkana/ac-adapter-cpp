#pragma once

#include <cstddef>
#include <vector>
#include <algorithm>
#include <numeric>

template <class Container, class=typename Container::value_type>
std::vector<std::size_t> suffix_array (Container const& s)
{
    if (s.empty())  return {};

    std::vector<std::size_t> c(s.size()), sa(s.size()), swp(s.size()), pos(s.size());

    // 1 文字目まで見てソートです。
    std::iota(std::begin(sa), std::end(sa), 0u);
    std::sort(std::begin(sa), std::end(sa), [&s](std::size_t i, std::size_t j) {
        return s.at(i)==s.at(j) ? i>j : s.at(i)<s.at(j); });

    // 1 文字目まで見た同値類です。
    // 1 文字しかないものは特別で、別同値類です。←ここが匠ポイントです。
    for (std::size_t i=1; i<s.size(); i++) {
        c.at(sa.at(i)) = sa.at(i-1)+1!=s.size() && s.at(sa.at(i-1))==s.at(sa.at(i))
            ? c.at(sa.at(i-1))
            : i
            ;
    }

    // 2*len 文字目まで見ましょう。
    for (std::size_t len=1; len<s.size(); len<<=1) {
        // 同値類ごとに、次に入る場所を管理です。
        std::iota(std::begin(pos), std::end(pos), 0u);

        // ソートです。
        // 長さの短いものとぴったりのものは、別です。
        swp = sa;
        for (std::size_t i : sa) if (len <= i) {
            swp.at(pos.at(c.at(i-len))++) = i-len;
        }
        swp.swap(sa);

        // 同値類です。
        // ピッタリのものは特別で、別同値類です。←ここが匠ポイントです。
        swp.at(sa.at(0)) = 0;
        for (std::size_t i=1; i<s.size(); i++) {
            std::size_t x=sa.at(i-1), y=sa.at(i);

            swp.at(y) = x+len<s.size()
                && c.at(x)==c.at(y)
                && c.at(x+len)==c.at(y+len)
                ? swp.at(x)
                : i
                ;
        }
        swp.swap(c);
    }
    return sa;
}

