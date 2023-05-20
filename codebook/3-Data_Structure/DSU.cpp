struct DSU {
    int n, cc;
    vector<int> to, siz;
    DSU() {}
    DSU(int n) : n(n), cc(n) {
        to = siz = vector<int>(n + 1, 1);
        iota(to.begin(), to.end(), 0);
    }
    int dsu(int x) {
        return x == to[x] ? x : (to[x] = dsu(to[x]));
    }
    bool same(int a, int b) {
        return dsu(a) == dsu(b);
    }
    bool Merge(int a, int b) {
        a = dsu(a), b = dsu(b);
        if (a == b) {
            return false;
        }
        cc--;
        if (siz[a] < siz[b]) {
            swap(a, b);
        }
        to[b] = a;
        siz[a] += siz[b];
        return true;
    }
};
