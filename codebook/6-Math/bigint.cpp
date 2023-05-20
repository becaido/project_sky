struct bigint : vector<int> {
    const static int base = 1e9, wid = log10(base);
    bool neg = false;
    bigint() {}
    bigint(string s) {
        if (s == "-0") {
            emplace_back(0);
            return;
        }
        if (s[0] == '-') {
            neg = true;
            s = s.substr(1);
        }
        for (int i = s.size() - 1, cnt = 0, val = 0, ten = 1; i >= 0; i--) {
            cnt++;
            val += (s[i] - '0') * ten;
            ten *= 10;
            if (i == 0 || cnt == wid) {
                emplace_back(val);
                cnt = val = 0;
                ten = 1;
            }
        }
    }
    template<typename T>
    bigint(const T& val) : bigint(to_string(val)) {}
    template<typename T>
    bigint& operator = (const T &rhs) {
        *this = bigint(rhs);
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
    int abscmp(const bigint& rhs) const {
        if (size() != rhs.size()) {
            return size() > rhs.size() ? 1 : -1;
        }
        for (int i = size() - 1; i >= 0; i--) {
            if ((*this)[i] != rhs[i]) {
                return (*this)[i] > rhs[i] ? 1 : -1;
            }
        }
        return 0;
    }
    int cmp(const bigint& rhs) const {
        if (neg != rhs.neg) {
            return neg == true ? -1 : 1;
        }
        return neg == true ? -abscmp(rhs) : abscmp(rhs);
    }
    bool operator < (const bigint& rhs) const {
        return cmp(rhs) < 0;
    }
    bool operator > (const bigint& rhs) const {
        return cmp(rhs) > 0;
    }
    bool operator <= (const bigint& rhs) const {
        return cmp(rhs) <= 0;
    }
    bool operator >= (const bigint& rhs) const {
        return cmp(rhs) >= 0;
    }
    bool operator == (const bigint& rhs) const {
        return cmp(rhs) == 0;
    }
    bool operator != (const bigint& rhs) const {
        return cmp(rhs) != 0;
    }
    bigint& operator += (const bigint& rhs) {
        return *this = *this + rhs;
    }
    bigint& operator ++ () {
        return *this = *this + 1;
    }
    bigint& operator -= (const bigint& rhs) {
        return *this = *this - rhs;
    }
    bigint& operator -- () {
        return *this = *this - 1;
    }
    bigint& operator *= (const bigint& rhs) {
        return *this = *this * rhs;
    }
    bigint& operator /= (const bigint& rhs) {
        return *this = *this / rhs;
    }
    bigint& operator %= (const bigint& rhs) {
        return *this = *this % rhs;
    }
    bigint abs() const {
        bigint re = *this;
        re.neg = false;
        return re;
    }
    void carry() {
        emplace_back(0);
        for (int i = 0; i < size(); i++) {
            if ((*this)[i] < 0) {
                (*this)[i] += base;
                (*this)[i + 1]--;
            }
            if ((*this)[i] >= base) {
                (*this)[i] -= base;
                (*this)[i + 1]++;
            }
        }
        while (size() && back() == 0) {
            pop_back();
        }
        if (size() == 0) {
            neg = false;
            emplace_back(0);
        }
    }
    bigint operator -() const {
        if (*this == 0) {
            return *this;
        }
        bigint re = *this;
        re.neg ^= 1;
        return re;
    }
    friend bigint operator + (bigint lhs, bigint rhs) {
        if (lhs.neg == true) {
            return -(-lhs + -rhs);
        }
        if (rhs.neg == true) {
            return lhs - -rhs;
        }
        if (lhs.size() < rhs.size()) {
            lhs.resize(rhs.size(), 0);
        }
        for (int i = 0; i < rhs.size(); i++) {
            lhs[i] += rhs[i];
        }
        lhs.carry();
        return lhs;
    }
    friend bigint operator - (bigint lhs, bigint rhs) {
        if (lhs.neg == true) {
            return -(-lhs - -rhs);
        }
        if (rhs.neg == true) {
            return lhs + -rhs;
        }
        if (lhs.abscmp(rhs) < 0) {
            return -(rhs - lhs);
        }
        for (int i = 0; i < rhs.size(); i++) {
            lhs[i] -= rhs[i];
        }
        lhs.carry();
        return lhs;
    }
    friend bigint operator * (bigint lhs, bigint rhs) {
        if (lhs == 0 || rhs == 0) {
            return 0;
        }
        bigint re;
        re.neg = lhs.neg ^ rhs.neg;
        vector<long long> tmp;
        auto add = [&](int i, long long val) {
            while (i >= tmp.size()) {
                tmp.emplace_back(0);
            }
            tmp[i] += val;
        };
        for (int i = 0; i < lhs.size(); i++) {
            for (int j = 0; j < rhs.size(); j++) {
                add(i + j, 1ll * lhs[i] * rhs[j]);
            }
            for (int j = 0; j < tmp.size(); j++) {
                if (tmp[j] >= base) {
                    add(j + 1, tmp[j] / base);
                    tmp[j] %= base;
                }
            }
        }
        re.resize(tmp.size());
        for (int i = 0; i < tmp.size(); i++) {
            re[i] = tmp[i];
        }
        return re;
    }
    friend bigint operator / (bigint lhs, bigint rhs) {
        assert(rhs != 0);
        if (lhs == 0) {
            return 0;
        }
        int norm = base / (rhs.back() + 1);
        bigint x = lhs.abs() * norm;
        bigint y = rhs.abs() * norm;
        bigint q, r;
        q.resize(x.size());
        for (int i = x.size() - 1; i >= 0; i--) {
            r = r * base + x[i];
            int s1 = r.size() <= y.size() ? 0 : r[y.size()];
            int s2 = r.size() < y.size() ? 0 : r[y.size() - 1];
            int d = (1ll * base * s1 + s2) / y.back();
            r = r - y * d;
            while (r.neg == true) {
                r += y;
                d--;
            }
            q[i] = d;
        }
        q.neg = lhs.neg ^ rhs.neg;
        q.carry();
        return q;
    }
    friend bigint operator % (bigint lhs, bigint rhs) {
        return lhs - (lhs / rhs) * rhs;
    }
    friend istream& operator >> (istream& ss, bigint& val) {
        string s;
        ss >> s;
        val = s;
        return ss;
    }
    friend ostream& operator << (ostream& ss, const bigint& val) {
        if (val.neg == true) {
            ss << '-';
        }
        ss << val.back();
        for (int i = (int)val.size() - 2; i >= 0; i--) {
            ss << string(wid - to_string(val[i]).size(), '0') << val[i];
        }
        return ss;
    }
};
