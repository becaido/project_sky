template<typename T = int>
struct LIS {
    vector<T> lis;
    LIS() {}
    void add(T val) {
        lis.emplace_back(val);
    }
    void work() {
        sort(lis.begin(), lis.end());
        lis.erase(unique(lis.begin(), lis.end()), lis.end());
    }
    T operator [] (const int &i) const {
        assert(0 <= i && i <= lis.size());
        return i == 0 ? 0 : lis[i - 1];
    }
    int operator () (const T& val) const {
        return lowb(val);
    }
    int lowb(const T& val) const {
        return lower_bound(lis.begin(), lis.end(), val) - lis.begin() + 1;
    }
    int uppb(const T& val) const {
        return upper_bound(lis.begin(), lis.end(), val) - lis.begin() + 1;
    }
};
