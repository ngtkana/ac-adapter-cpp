/*
 * @title HL 分解 (heavy-light decomposition)
 * @docs graph/tree/hl_decomposition.md
 */

#pragma once

#include <cassert>
#include <cstddef>
#include <utility>
#include <algorithm>
#include <vector>

class hl_decomposition {

private:
    bool built = false;
    std::size_t time;

    void erase_prt_dfs(std::size_t x, std::size_t p)
    {
        auto&& v = g.at(x);
        auto p_found = std::find(v.begin(), v.end(), p);
        if (p_found!= v.end()) v.erase(p_found);
        for (std::size_t& y : v) {
            erase_prt_dfs(y, x);
        }
    }

    void size_dfs(std::size_t x)
    {
        auto&& v = g.at(x);
        for (std::size_t& y : v) {
            size_dfs(y);
            sz.at(x) += sz.at(y);
            if (sz.at(v.front()) < sz.at(y)) {
                std::swap(v.front(), y);
            }
        }
    }

    void head_dfs(std::size_t x)
    {
        vid.at(x) = time++;
        auto&& v = g.at(x);

        for (std::size_t y : v) {
            head.at(y) = y==v.front()
                ? head.at(x)
                : y
                ;
            head_dfs(y);
        }
    }

public:
    std::vector<std::size_t> sz, head, vid;
    std::vector<std::vector<std::size_t>> g;

    hl_decomposition()=default;
    hl_decomposition(hl_decomposition const&)=default;
    hl_decomposition(hl_decomposition&&)=default;
    hl_decomposition& operator=(hl_decomposition const&)=default;
    hl_decomposition& operator=(hl_decomposition&&)=default;
    ~hl_decomposition()=default;

    hl_decomposition(std::vector<std::vector<std::size_t>> const& g_, std::size_t root)
        : g(g_)
    {
        assert(root < size());
        build(root);
    }

    hl_decomposition(std::size_t n) : g(n) {}

    void insert(std::size_t u, std::size_t v) {
        assert(u < size() && v < size());
        g.at(u).push_back(v);
        g.at(v).push_back(u);
    }

    void build(std::size_t root)
    {
        assert(!std::exchange(built, true));
        assert(root < size());

        time = 0;
        sz.assign(size(), 1u);
        head.resize(size());
        vid.resize(size());

        head.at(root) = root;

        erase_prt_dfs(root, root);
        size_dfs(root);
        head_dfs(root);
    }

    std::size_t size() const { return g.size(); }
};
