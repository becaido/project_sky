template<typename T>
struct LazySegtree {
    int n;
    vector<T> node;
    function<void(int, int, int)> Push, Pull, Assign;
    LazySegtree() {}
    LazySegtree(int n) : n(n) {
        node = vector<T>(4 * n + 1, T());
    }
    template<typename U>
    void build(U* a) {
        build(1, 1, n, a);
    }
    template<typename U>
    void build(int pos, int l, int r, U* a) {
        if (l == r) {
            node[pos].mx = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(pos << 1, l, mid, a);
        build(pos << 1 | 1, mid + 1, r, a);
        node[pos] = node[pos << 1] + node[pos << 1 | 1];
    }
    template<typename U>
    void upd(int l, int r, U x, function<void(T&, U)> Assign) {
        upd(1, l, r, 1, n, x, Assign);
    }
    template<typename U>
    void upd(int pos, int l, int r, int L, int R, U x, function<void(T&, U)> Assign) {
        if (l == L && r == R) {
            Assign(node[pos], x);
            return;
        }
        Push(pos, L, R);
        int mid = (L + R) / 2;
        if (r <= mid) {
            upd(pos << 1, l, r, L, mid, x, Assign);
        } else if (l > mid) {
            upd(pos << 1 | 1, l, r, mid + 1, R, x, Assign);
        } else {
            upd(pos << 1, l, mid, L, mid, x, Assign);
            upd(pos << 1 | 1, mid + 1, r, mid + 1, R, x, Assign);
        }
        Pull(pos, L, R);
    }
    T que(int l, int r) {
        return que(1, l, r, 1, n);
    }
    T que(int pos, int l, int r, int L, int R) {
        Push(pos, L, R);
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
