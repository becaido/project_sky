struct LCA { // need adj
    int n;
    vector<vector<int>> to;
    vector<int> h;
    LCA() {}
    LCA(int n) : n(n) {
        to = vector<vector<int>>(n + 1, vector<int>(__lg(n) + 2, 0));
        h = vector<int>(n + 1, 0);
    }
    void dfs(int pos) {
        for (int np : adj[pos]) {
            if (np != to[pos][0]) {
                h[np] = h[pos] + 1;
                to[np][0] = pos;
                dfs(np);
            }
        }
    }
    void build(int root = 1) {
        h[root] = 1;
        dfs(root);
        for (int j = 1; j <= __lg(n) + 1; j++) {
            for (int i = 1; i <= n; i++) {
                to[i][j] = to[to[i][j - 1]][j - 1];
            }
        }
    }
    int jump(int pos, int k) {
        int cnt = 0;
        while (k) {
            if (k & 1) {
                pos = to[pos][cnt];
            }
            cnt++;
            k >>= 1;
        }
        return pos;
    }
    int lca(int a, int b) {
        if (h[a] < h[b]) {
            swap(a, b);
        }
        a = jump(a, h[a] - h[b]);
        if (a == b) {
            return a;
        }
        for (int i = __lg(n) + 1; i >= 0; i--) {
            if (to[a][i] != to[b][i]) {
                a = to[a][i];
                b = to[b][i];
            }
        }
        return to[a][0];
    }
};
