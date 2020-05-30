#ifndef OTHERS_INCREMENTAL_SUM_HPP
#define OTHERS_INCREMENTAL_SUM_HPP

#include "cstdint2.hpp"
#include "vec.hpp"
#include <algorithm>

template <class Group>
class incremental_sum {
    using this_type = incremental_sum<Group>;
    using group_type = Group;
    using value_type = typename group_type::value_type;

public:
    usize frozen;
    vec<value_type> table;

    incremental_sum()=default;
    incremental_sum(incremental_sum const&)=default;
    incremental_sum(incremental_sum&&)=default;
    incremental_sum& operator=(incremental_sum const&)=default;
    incremental_sum& operator=(incremental_sum&&)=default;
    ~incremental_sum()=default;

    incremental_sum(usize n)
        : frozen(0), table(n+1) {}

    incremental_sum(usize n, value_type x)
        : frozen(0), table(n+1, x)
    {
        std::partial_sum(table.begin(), table.end(), table.begin());
    }

    incremental_sum(vec<value_type> const& v)
        : frozen(0), table(v.size() + 1)
    {
        std::partial_sum(v.begin(), v.end(), table.begin() + 1);
    }

    this_type& set(usize i, value_type x) {
        assert(frozen == i);
        frozen++;
        table.at(i+1) = group_type::op(table.at(i), x);
        return *this;
    }

    value_type fold(usize l, usize r) {
        return group_type::sub(table.at(r), table.at(l));
    }

    vec<value_type> to_vec() const {
        vec<value_type> ans(table.size()-1);
        for (usize i=0; i<frozen; i++) {
            ans.at(i) = table.at(i+1) - table.at(i);
        }
        return ans;
    }
};

#endif
