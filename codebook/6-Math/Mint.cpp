struct Mint {
    const static int MOD = 998244353;
    int val = 0;
    int norm(int x) const {
        if (x < 0) {
            x += MOD;
        }
        if (x >= MOD) {
            x -= MOD;
        }
        return x;
    }
    Mint() {}
    template<typename T>
    Mint(const T& x) : val(norm(x % MOD)) {}
    template<typename T>
    Mint& operator = (const T &rhs) {
        *this = Mint(rhs);
        return *this;
    }
    template<typename T>
    operator T() {
        stringstream ss;
        ss << *this;
        T re;
        ss >> re;
        return re;
    }
    int cmp(const Mint& rhs) const {
        return val > rhs.val ? 1 : val == rhs.val ? 0 : -1;
    }
    bool operator < (const Mint& rhs) const {
        return cmp(rhs) < 0;
    }
    bool operator > (const Mint& rhs) const {
        return cmp(rhs) > 0;
    }
    bool operator <= (const Mint& rhs) const {
        return cmp(rhs) <= 0;
    }
    bool operator >= (const Mint& rhs) const {
        return cmp(rhs) >= 0;
    }
    bool operator == (const Mint& rhs) const {
        return cmp(rhs) == 0;
    }
    bool operator != (const Mint& rhs) const {
        return cmp(rhs) != 0;
    }
    Mint inv() const {
        assert(val != 0);
        Mint re(1), d(val);
        int up = MOD - 2;
        while (up) {
            if (up & 1) {
                re *= d;
            }
            d *= d;
            up >>= 1;
        }
        return re;
    }
    Mint& operator += (const Mint& rhs) {
        val = norm(val + rhs.val);
        return *this;
    }
    Mint& operator ++ () {
        return *this += 1;
    }
    Mint& operator -= (const Mint& rhs) {
        val = norm(val - rhs.val);
        return *this;
    }
    Mint& operator -- () {
        return *this -= 1;
    }
    Mint& operator *= (const Mint& rhs) {
        val = 1ll * val * rhs.val % MOD;
        return *this;
    }
    Mint& operator /= (const Mint& rhs) {
        return *this *= rhs.inv();
    }
    Mint operator -() const {
        return norm(MOD - val);
    }
    friend Mint operator + (const Mint& lhs, const Mint& rhs) {
        Mint re = lhs;
        re += rhs;
        return re;
    }
    friend Mint operator - (const Mint& lhs, const Mint& rhs) {
        Mint re = lhs;
        re -= rhs;
        return re;
    }
    friend Mint operator * (const Mint& lhs, const Mint& rhs) {
        Mint re = lhs;
        re *= rhs;
        return re;
    }
    friend Mint operator / (const Mint& lhs, const Mint& rhs) {
        Mint re = lhs;
        re /= rhs;
        return re;
    }
    friend istream& operator >> (istream& ss, Mint& x) {
        long long y;
        ss >> y;
        x = Mint(y);
        return ss;
    }
    friend ostream& operator << (ostream& ss, const Mint& x) {
        return ss << x.val;
    }
};
