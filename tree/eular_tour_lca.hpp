#pragma once

#include <cstddef>
#include <cassert>
#include <utility>
#include <algorithm>
#include <vector>

struct eular_tour_lca
{
    std::vector<std::size_t> in_pos;
    std::vector<std::pair<std::size_t, std::size_t>> table;

    eular_tour_lca()=default;
    eular_tour_lca(eular_tour_lca const&)=default;
    eular_tour_lca(eular_tour_lca&&)=default;
    eular_tour_lca& operator=(eular_tour_lca const&)=default;
    eular_tour_lca& operator=(eular_tour_lca&&)=default;
    ~eular_tour_lca()=default;

    eular_tour_lca(std::vector<std::vector<std::size_t>> const& g)
        : in_pos(g.size()), table(4*g.size()-2)
    {
        std::vector<std::size_t> ord, depth(g.size());
        auto dfs = [&](auto&&f, std::size_t x, std::size_t p) -> void {
            in_pos.at(x) = ord.size();
            ord.push_back(x);
            for (std::size_t y : g.at(x)) if (y!=p) {
                depth.at(y) = depth.at(x) + 1;
                f(f, y, x);
                ord.push_back(x);
            };
        };
        dfs(dfs, 0, 0);
        assert(ord.size()==2*g.size()-1);

        for (std::size_t i=0; i<table.size()>>1; i++) {
            table.at((table.size()>>1)+i) = { depth.at(ord.at(i)), ord.at(i) };
        }
        for (std::size_t i=(table.size()>>1)-1; i; i--) {
            table.at(i) = std::min(table.at(2*i), table.at(2*i+1));
        }
    }

    std::size_t get_lca(std::size_t l, std::size_t r) const
    {
        if (l==r) return l;
        l = in_pos.at(l);
        r = in_pos.at(r);
        if (l>r) std::swap(l, r);

        std::pair<std::size_t, std::size_t> fold = {table.size(), table.size()};
        for (l+=table.size()>>1, r+=table.size()>>1; l<r; l>>=1, r>>=1)
        {
            if (l&1) fold = std::min(fold, table.at(l++));
            if (r&1) fold = std::min(fold, table.at(--r));
        }
        return fold.second;
    }
};

/*
 * @title Eular tour による LCA (LCA by Eular tour)
 * @docs tree/eular_tour_lca.md
 */
