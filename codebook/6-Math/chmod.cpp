int turn (int x, int mod) {
    x %= mod;
    return x < 0 ? x + mod : x;
}

int exgcd (int a, int b, int &A, int &B, int mod) {
    if (b == 0) {
        A = 1, B = 0;
        return a;
    }
    int re = exgcd (b, a % b, A, B, mod);
    int AA = B, BB = A - B * (a / b);
    A = AA, B = turn (BB, mod);
    return re;
}

int chmod (vector<pair<int, int>> v) {
    int M = 1;
    for (auto [m, a] : v) {
        M *= m;
    }
    int re = 0;
    for (auto [m, a] : v) {
        int A, B;
        exgcd (M / m, m, A, B, m);
        cerr << M / m << ' ' << m << ' ' << A << ' ' << B << '\n';
        re = turn (re + A * (M / m) * a, M);
    }
    return re;
}
