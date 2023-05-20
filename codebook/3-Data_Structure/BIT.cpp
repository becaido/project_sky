template<typename T = int>
struct BIT {
    int n;
    T val = 0;
    vector<T> bit;
    bool pre = true;
    function<T(T, T)> add = [&](T x, T y) {
        return x + y;
    };
    function<T(T, T)> del = [&](T x, T y) {
        return x - y;
    };
    BIT() {}
    BIT(int n, T val = 0, bool pre = true) : n(n), val(val), pre(pre) {
        bit = vector<T>(n + 1, val);
    }
    void upd(int pos, T x) {
        if (pos <= 0 || pos > n) {
            return;
        }
        if (pre == true) {
            for (; pos <= n; pos += pos & -pos) {
                bit[pos] = add(bit[pos], x);
            }
        } else {
            for (; pos; pos -= pos & -pos) {
                bit[pos] = add(bit[pos], x);
            }
        }
    }
    T que(int pos) {
        if (pos <= 0 || pos > n) {
            return val;
        }
        T re = val;
        if (pre == true) {
            for (; pos; pos -= pos & -pos) {
                re = add(re, bit[pos]);
            }
        } else {
            for (; pos <= n; pos += pos & -pos) {
                re = add(re, bit[pos]);
            }
        }
        return re;
    }
    T que(int l, int r) {
        if (pre == true) {
            return del(que(r), que(l - 1));
        } else {
            return del(que(l), que(r + 1));
        }
    }
    int sch(T val) {
        int pos = 0;
        T sum = 0;
        for (int i = __lg(n); i >= 0; i--) {
            if (pos + (1 << i) <= n && add(sum, bit[pos + (1 << i)]) < val) {
                sum = add(sum, bit[pos += 1 << i]);
            }
        }
        return pos + 1;
    }
};
