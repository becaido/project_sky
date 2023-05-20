struct Rollback_DSU {
    int n;
    vector<int> to, siz;
    vector<pair<int, int>> op;
    DSU() {}
    DSU(int n) : n(n) {
        to = siz = vector<int>(n + 1, 1);
        iota(to.begin(), to.end(), 0);
    }
    int dsu(int x) {
        return x == to[x] ? x : dsu(to[x]);
    }
    bool same(int a, int b) {
        return dsu(a) == dsu(b);
    }
    bool Merge(int a, int b) {
        a = dsu(a), b = dsu(b);
        if (a == b) {
            return false;
        }
        if (siz[a] < siz[b]) {
            swap(a, b);
        }
        op.emplace_back(a, b);
        to[b] = a;
        siz[a] += siz[b];
        return true;
    }
    void rollback() {
        if (op.size()) {
            auto [a, b] = op.back();
            op.pop_back();
            to[b] = b;
            siz[a] -= siz[b];
        }
    }
    void Reset(int k) {
        while (op.size() > k) {
            rollback();
        }
    }
};
