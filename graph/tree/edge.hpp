#pragma once

#include <iostream>

template <class Weight>
struct edge {
    std::size_t to;
    Weight weight;

    edge()=default;
    edge(edge const&)=default;
    edge(edge&&)=default;
    edge& operator=(edge const&)=default;
    edge& operator=(edge&&)=default;
    ~edge()=default;

    edge(std::size_t to_, Weight weight_)
        : to(to_), weight(weight_) {}
};

template <class Weight> std::ostream&
operator<< (std::ostream& os, edge<Weight> e)
{
    return os << '(' << e.to << ',' << e.weight << ')';
}
