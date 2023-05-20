vector<int> SA (string s) {
    int n = s.size();
    if (n == 1) return {1};
    s += string (1, 0);
    vector<int> sa (n + 1), rnk (n + 1), cnt (n + 1);
    int al[256] = {};
    FOR (i, 0, n) al[s[i]]++;
    FOR (i, 1, 255) al[i] += al[i - 1];
    FOR (i, 0, n) sa[--al[s[i]]] = i;
    for (int i = 1, now = 0; i <= n; i++) {
        if (s[sa[i]] != s[sa[i - 1]]) now++;
        rnk[sa[i]] = now;
    }
    for (int len = 1; len <= n; len <<= 1) {
        vector<int> lp (n + 1), tmp (n + 1);
        fill (cnt.begin(), cnt.end(), 0);
        FOR (i, 0, n) {
            lp[i] = sa[i] - len;
            lp[i] += lp[i] < 0 ? n + 1 : 0;
            cnt[rnk[i]]++;
        }
        FOR (i, 1, n) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 0; i--) sa[--cnt[rnk[lp[i]]]] = lp[i];
        tmp[sa[0]] = 0;
        for (int i = 1, now = 0; i <= n; i++) {
            int np1 = sa[i] + len, np2 = sa[i - 1] + len;
            np1 -= np1 > n + 1 ? n + 1 : 0;
            np2 -= np2 > n + 1 ? n + 1 : 0;
            if (rnk[sa[i]] != rnk[sa[i - 1]] || rnk[np1] != rnk[np2]) now++;
            tmp[sa[i]] = now;
        }
        rnk = tmp;
    }
    sa.erase (sa.begin());
    return sa;
}

vector<int> LCP (string s, vector<int> sa) {
    int n = s.size(), len = 0;
    vector<int> rnk (n), lcp (n - 1);
    for (int i = 0; i < n; i++) rnk[sa[i]] = i;
    for (int i = 0; i < n; i++) {
        if (rnk[i] == n - 1) {
            len = 0;
            continue;
        }
        int j = sa[rnk[i] + 1];
        while (i + len < n && j + len < n && s[i + len] == s[j + len]) len++;
        lcp[rnk[i]] = len;
        len = max (0, len - 1);
    }
    return lcp;
}
