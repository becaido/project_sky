const int MOD = 1e9 + 7;
const int G = 3;
const int mod[3] = {998244353, 167772161, 469762049};

int power (int d, int up) {
    int ans = 1;
    while (up) {
        if (up & 1) ans = 1ll * ans * d % MOD;
        d = 1ll * d * d % MOD;
        up >>= 1;
    }
    return ans;
}

int power (int d, int up, int t) {
    int ans = 1;
    while (up) {
        if (up & 1) ans = 1ll * ans * d % mod[t];
        d = 1ll * d * d % mod[t];
        up >>= 1;
    }
    return ans;
}

void NTT (int a[], int n, bool b) {
    for (int i = 0, j = 0; i < n; i++) {
        if (i < j) swap (a[i], a[j]);
        for (int k = n >> 1; (j ^= k) < k; k >>= 1);
    }
    for (int len = 1; len < n; len <<= 1) {
        int w = power (G, (MOD - 1) / (len << 1));
        if (b) w = power (w, MOD - 2);
        for (int i = 0; i < n; i += len << 1) {
            int now = 1;
            for (int j = 0; j < len; j++) {
                int x = a[i + j], y = 1ll * a[i + j + len] * now % MOD;
                a[i + j] = (x + y >= MOD ? x + y - MOD : x + y);
                a[i + j + len] = (x - y < 0 ? x - y + MOD : x - y);
                now = 1ll * now * w % MOD;
            }
        }
    }
    int x = power (n, MOD - 2);
    if (b) for (int i = 0; i < n; i++) a[i] = 1ll * a[i] * x % MOD;
}

void NTT (int a[], int n, int t, bool b) {
    for (int i = 0, j = 0; i < n; i++) {
        if (i < j) swap (a[i], a[j]);
        for (int k = n >> 1; (j ^= k) < k; k >>= 1);
    }
    for (int len = 1; len < n; len <<= 1) {
        int w = power (G, (mod[t] - 1) / (len << 1), t);
        if (b) w = power (w, mod[t] - 2, t);
        for (int i = 0; i < n; i += len << 1) {
            int now = 1;
            for (int j = 0; j < len; j++) {
                int x = a[i + j], y = 1ll * a[i + j + len] * now % mod[t];
                a[i + j] = (x + y >= mod[t] ? x + y - mod[t] : x + y);
                a[i + j + len] = (x - y < 0 ? x - y + mod[t] : x - y);
                now = 1ll * now * w % mod[t];
            }
        }
    }
    int x = power (n, mod[t] - 2, t);
    if (b) for (int i = 0; i < n; i++) a[i] = 1ll * a[i] * x % mod[t];
}

void getMOD (int a[], int a1[], int a2[], int a3[], int n) {
    for (int i = 0; i < n; i++) {
        ll x = ((__int128) a1[i] * mod[1] * power (mod[1], mod[0] - 2, 0) + (__int128) a1[i] * mod[0] * power (mod[0], mod[1] - 2, 1)) % (1ll * mod[0] * mod[1]);
        int k = (a2[i] - x) % mod[2] * power (1ll * mod[0] * mod[1] % mod[2], mod[2] - 2, 2) % mod[2];
        if (k < 0) k += mod[2];
        a[i] = (1ll * k * mod[0] % MOD * mod[1] + x) % MOD;
    }
}

#define Poly vector<int>

const int MOD = 998244353;
const int G = 3;

int power (int d, int up) {
    int ans = 1;
    while (up) {
        if (up & 1) ans = 1ll * ans * d % MOD;
        d = 1ll * d * d % MOD;
        up >>= 1;
    }
    return ans;
}

Poly NTT (Poly a, bool b) {
    int n = a.size();
    for (int i = 0, j = 0; i < n; i++) {
        if (i < j) swap (a[i], a[j]);
        for (int k = n >> 1; (j ^= k) < k; k >>= 1);
    }
    for (int len = 1; len < n; len <<= 1) {
        int w = power (G, (MOD - 1) / (len << 1));
        if (b) w = power (w, MOD - 2);
        for (int i = 0; i < n; i += len << 1) {
            int now = 1;
            for (int j = 0; j < len; j++) {
                int x = a[i + j], y = 1ll * a[i + j + len] * now % MOD;
                a[i + j] = (x + y >= MOD ? x + y - MOD : x + y);
                a[i + j + len] = (x - y < 0 ? x - y + MOD : x - y);
                now = 1ll * now * w % MOD;
            }
        }
    }
    int x = power (n, MOD - 2);
    if (b) for (int i = 0; i < n; i++) a[i] = 1ll * a[i] * x % MOD;
    return a;
}

Poly Mult (Poly a, Poly b) {
    int n = a.size();
    a.resize (n << 1, 0);
    b.resize (n << 1, 0);
    a = NTT (a, 0);
    b = NTT (b, 0);
    for (int i = 0; i < (n << 1); i++) a[i] = 1ll * a[i] * b[i] % MOD;
    a = NTT (a, 1);
    a.resize (n);
    return a;
}

Poly Inv (Poly a) {
    int n = a.size();
    Poly b = Poly (1, power (a[0], MOD - 2));
    for (int len = 2; len <= n; len <<= 1) {
        Poly tmp (len << 1, 0);
        for (int i = 0; i < len; i++) tmp[i] = a[i];
        b.resize (len << 1, 0);
        tmp = NTT (tmp, 0);
        b = NTT (b, 0);
        for (int i = 0; i < (len << 1); i++) {
            b[i] = (2 - 1ll * b[i] * tmp[i]) % MOD * b[i] % MOD;
            if (b[i] < 0) b[i] += MOD;
        }
        b = NTT (b, 1);
        b.resize (len);
    }
    return b;
}

Poly Divis (Poly a, Poly b) {
    if (a.size() < b.size()) return Poly (1, 0);
    int n = a.size(), m = b.size();
    reverse (a.begin(), a.end());
    reverse (b.begin(), b.end());
    int siz = 1 << (__lg (n - m + 1) + 1);
    a.resize (siz);
    b.resize (siz);
    a = Mult (a, Inv (b));
    a.resize (n - m + 1);
    reverse (a.begin(), a.end());
    return a;
}

Poly Remain (Poly a, Poly b) {
    if (b.size() == 1) return Poly (1, 0);
    Poly c = Divis (a, b);
    int m = b.size(), siz = 1 << (__lg (m) + 1);
    b.resize (siz);
    c.resize (siz);
    b = Mult (b, c);
    m--;
    a.resize (m);
    b.resize (m);
    for (int i = 0; i < m; i++) {
        a[i] -= b[i];
        a[i] += a[i] < 0 ? MOD : 0;
    }
    return a;
}

Poly Integ (Poly a) {
    int n = a.size();
    for (int i = n - 1; i >= 1; i--) a[i] = 1ll * a[i - 1] * power (i, MOD - 2) % MOD;
    a[0] = 0;
    return a;
}

Poly Deriv (Poly a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) a[i] = 1ll * a[i + 1] * (i + 1) % MOD;
    a[n - 1] = 0;
    return a;
}

Poly Ln (Poly a) {
    int n = a.size();
    Poly b = Inv (a);
    a = Deriv (a);
    a = Mult (a, b);
    return Integ (a);
}

Poly Exp (Poly a) {
    int n = a.size();
    Poly b = Poly (1, 1);
    for (int len = 2; len <= n; len <<= 1) {
        b.resize (len, 0);
        Poly tmp = Ln (b);
        for (int i = 0; i < len; i++) {
            tmp[i] = a[i] - tmp[i];
            if (tmp[i] < 0) tmp[i] += MOD;
        }
        tmp[0] = (tmp[0] == MOD - 1 ? 0 : tmp[0] + 1);
        b = Mult (b, tmp);
    }
    return b;
}
