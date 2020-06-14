class union_find {
    std::vector<i32> p;

    public:
    union_find()=default;
    union_find(union_find const&)=default;
    union_find(union_find&&)=default;
    union_find& operator=(union_find const&)=default;
    union_find& operator=(union_find&&)=default;
    ~union_find()=default;

    union_find(i32 n)
        : p(n, -1) {}

    auto get_i32ernal_table() const { return p; }
    bool is_root(i32 i) const { return p.at(i) < 0; }
    i32 root(i32 i) { return is_root(i) ? i : p.at(i) = root(p.at(i)); }
    i32 size(i32 i) { return -p.at(root(i)); }
    usize size() const { return p.size(); }

    bool unite(i32 i, i32 j) {
        i = root(i);
        j = root(j);
        if (i==j) return false;
        if (size(i) > size(j)) std::swap(i, j);

        p.at(j) += p.at(i);
        p.at(i) = j;
        return true;
    }

    std::string debug() {
        vec<vec<i32>> mems(size());
        for (i32 i=0; i<(i32)size(); i++) mems.at(root(i)).push_back(i);
        mems.resize(std::remove_if(mems.begin(), mems.end(), [](auto&& v){ return v.empty(); }) - mems.begin());
        std::stringstream ss;
        ss << '{';
        for (usize i=0; i<mems.size(); i++) {
            ss << (i ? "|" : "");
            auto&& v = mems.at(i);
            for (usize j=0; j<v.size(); j++) {
                ss << (j ? "," : "") << v.at(j);
            }
        }
        ss << '}';
        return ss.str();
    }
};
