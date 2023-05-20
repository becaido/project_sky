namespace FFT {

using cpx = complex<double>;

const double pi = acos(-1);
const double eps = 1e-6;

inline vector<cpx> fft(vector<cpx> a, bool dft = false) { // n = 2^k
    int n = a.size();
    if (n <= 1) {
        return a;
    }
    assert(__builtin_popcount(n) == 1);
    vector<cpx> w(n);
    for (int i = 0; i < n; i++) {
        double theta = (2 * pi) * i / n;
        theta *= (dft == true ? -1 : 1);
        w[i] = cpx(cos(theta), sin(theta));
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
                cpx val = a[i + j + len] * w[n / (len << 1) * j];
                a[i + j + len] = a[i + j] - val;
                a[i + j] += val;
            }
        }
    }
    if (dft == true) {
        for (int i = 0; i < n; i++) {
            a[i] /= n;
        }
    }
    return a;
}

inline vector<cpx> Mul(vector<cpx> a, vector<cpx> b) {
    int sz = 1;
    while (sz < a.size() || sz < b.size()) {
        sz <<= 1;
    }
    sz <<= 1;
    a.resize(sz, 0);
    b.resize(sz, 0);
    a = fft(a), b = fft(b);
    for (int i = 0; i < sz; i++) {
        a[i] *= b[i];
    }
    a = fft(a, true);
    while (a.size() > 1 && abs(a.back().real()) < eps) {
        a.pop_back();
    }
    return a;
}

template<typename T = int>
vector<T> mul(vector<T> a, vector<T> b) {
    int n = a.size(), m = b.size();
    vector<cpx> ca(n), cb(m);
    for (int i = 0; i < n; i++) {
        ca[i] = a[i];
    }
    for (int i = 0; i < m; i++) {
        cb[i] = b[i];
    }
    ca = Mul(ca, cb);
    a.resize(n = ca.size());
    for (int i = 0; i < a.size(); i++) {
        a[i] = ca[i].real() + (ca[i].real() > 0 ? eps : -eps);
    }
    return a;
}

}
