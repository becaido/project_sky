template<typename T>
struct Segtree {
    int n = 0;
    vector<T> node;
    Segtree() {}
    Segtree(int n) : n(n) {
        node = vector<T>(4 * n + 1, T());
    }
    template<typename U>
    void build(U* a) {
        build(1, 1, n, a);
    }
    template<typename U>
    void build(int pos, int l, int r, U* a) {
        if (l == r) {
            node[pos] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(pos << 1, l, mid, a);
        build(pos << 1 | 1, mid + 1, r, a);
        node[pos] = node[pos << 1] + node[pos << 1 | 1];
    }
    template<typename U>
    void upd(int p, U x) {
        upd(1, 1, n, p, x);
    }
    template<typename U>
    void upd(int pos, int l, int r, int p, U x) {
        if (l == r) {
            node[pos] = x;
            return;
        }
        int mid = (l + r) / 2;
        if (p <= mid) {
            upd(pos << 1, l, mid, p, x);
        } else {
            upd(pos << 1 | 1, mid + 1, r, p, x);
        }
        node[pos] = node[pos << 1] + node[pos << 1 | 1];
    }
    T que(int l, int r) {
        return que(1, l, r, 1, n);
    }
    T que(int pos, int l, int r, int L, int R) {
        if (l == L && r == R) {
            return node[pos];
        }
        int mid = (L + R) / 2;
        if (r <= mid) {
            return que(pos << 1, l, r, L, mid);
        }
        if (l > mid) {
            return que(pos << 1 | 1, l, r, mid + 1, R);
        }
        return que(pos << 1, l, mid, L, mid) + que(pos << 1 | 1, mid + 1, r, mid + 1, R);
    }
};
