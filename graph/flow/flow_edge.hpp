#pragma once

#include <iostream>
#include <cstddef>

template <class Flow> struct flow_edge {
    std::size_t to;
    std::size_t rev;
    Flow cap;

    // special member functions
    flow_edge()=default;
    flow_edge(const flow_edge&)=default;
    flow_edge(flow_edge&&)=default;
    flow_edge&operator=(const flow_edge&)=default;
    flow_edge&operator=(flow_edge&&)=default;
    ~flow_edge()=default;

    flow_edge(std::size_t to_, std::size_t rev_, Flow cap_)
        : to(to_), rev(rev_), cap(cap_) {}
};

template <class Flow> std::ostream& operator<<(std::ostream& os, flow_edge<Flow> e) {
    return os << "(" << e.to << "," << e.cap << ")";
}
