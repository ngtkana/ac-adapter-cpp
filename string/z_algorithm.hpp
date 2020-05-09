#pragma once

#include <cstddef>
#include <vector>

template <class Container, class=typename Container::value_type>
std::vector<std::size_t> z_algorhthm (Container const& s)
{
    std::vector<std::size_t> z(s.size());

    if (s.empty()) {
        return z;
    }

    for (std::size_t i=1, j=0; i<s.size(); ) {
        for (; i+j<s.size() && s.at(j)==s.at(i+j); j++);
        z.at(i) = j;

        if (j==0) {
            i++;
            continue;
        }

        std::size_t k=1;
        for (; i+k<s.size() && k+z.at(k)<j; k++) {
            z.at(i+k) = z.at(k);
        }
        i += k;
        j -= k;
    }
    z.at(0) = s.size();

    return z;
}
