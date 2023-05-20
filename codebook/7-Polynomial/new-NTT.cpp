namespace NTT { // need Mint, power

using Poly = vector<Mint>;

const int G = 3;

inline Poly ntt(Poly a, bool dntt = false) { // n = 2^k
    int n = a.size();
    if (n <= 1) {
        return a;
    }
    assert(__builtin_popcount(n) == 1);
    vector<Mint> w(n);
    w[0] = 1, w[1] = power(G, (Mint::MOD - 1) / n);
    if (dntt == true) {
        w[1] = w[1].inv();
    }
    for (int i = 2; i < n; i++) {
        w[i] = w[i - 1] * w[1];
    }
    vector<int> rev(n);
    for (int i = 0; i < n; i++) {
        rev[i] = (rev[i >> 1] | (i & 1 ? n : 0)) >> 1;
        if (i < rev[i]) {
            swap(a[i], a[rev[i]]);
        }
    }
    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += len << 1) {
            for (int j = 0; j < len; j++) {
                Mint val = a[i + j + len] * w[n / (len << 1) * j];
                a[i + j + len] = a[i + j] - val;
                a[i + j] += val;
            }
        }
    }
    if (dntt == true) {
        Mint invn = power(n, -1);
        for (int i = 0; i < n; i++) {
            a[i] *= invn;
        }
    }
    return a;
}

inline Poly mul(Poly a, Poly b) {
    int sz = 1;
    while (sz < a.size() || sz < b.size()) {
        sz <<= 1;
    }
    sz <<= 1;
    a.resize(sz, 0);
    b.resize(sz, 0);
    a = ntt(a), b = ntt(b);
    for (int i = 0; i < sz; i++) {
        a[i] *= b[i];
    }
    a = ntt(a, true);
    while (a.size() > 1 && a.back() == 0) {
        a.pop_back();
    }
    return a;
}

inline Poly inv(Poly a) { // a[0] != 0
    assert(a[0] != 0);
    int n = a.size(), sz = 1;
    while (sz < a.size()) {
        sz <<= 1;
    }
    a.resize(sz);
    Poly b(1, a[0].inv());
    for (int len = 2; len <= sz; len <<= 1) {
        Poly c(len << 1, 0);
        b.resize(len << 1, 0);
        for (int i = 0; i < len; i++) {
            c[i] = a[i];
        }
        b = ntt(b), c = ntt(c);
        for (int i = 0; i < (len << 1); i++) {
            b[i] *= 2 - b[i] * c[i];
        }
        b = ntt(b, true);
        b.resize(len);
    }
    b.resize(n);
    return b;
}

inline Poly div(Poly a, Poly b) {
    if (a.size() < b.size()) {
        return Poly(1, 0);
    }
    int n = a.size(), m = b.size();
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    b.resize(n - m + 1);
    a = mul(a, inv(b));
    a.resize(n - m + 1);
    reverse(a.begin(), a.end());
    return a;
}

inline Poly rem(Poly a, Poly b) {
    if (a.size() < b.size()) {
        return a;
    }
    b = mul(b, div(a, b));
    for (int i = 0; i < b.size(); i++) {
        a[i] -= b[i];
    }
    while (a.size() > 1 && a.back() == 0) {
        a.pop_back();
    }
    return a;
}

}
