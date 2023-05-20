struct Bimatch {
    int n, m;
    vector<int> adj[SIZE];
    int mx[SIZE], my[SIZE];
    bool vs[SIZE];
    Bimatch() {}
    Bimatch (int n, int m) : n (n), m (m) {
        fill (adj, adj + n + 1, vector<int>());
        fill (mx, mx + n + 1, 0);
        fill (my, my + m + 1, 0);
    }
    void add (int a, int b) {
        adj[a].pb (b);
    }
    bool dfs (int x) {
        for (int y : adj[x]) {
            if (vs[y]) continue;
            vs[y] = 1;
            if (my[y] == 0 || dfs (my[y])) {
                my[mx[x] = y] = x;
                return 1;
            }
        }
        return 0;
    }
    int deal() {
        int cnt = 0;
        FOR (i, 1, n) {
            fill (vs, vs + m + 1, 0);
            cnt += dfs (i);
        }
        return cnt;
    }
};

template<typename T = int, typename U = int>
struct KM {
    const T INF = numeric_limits<T>::max();
    int n;
    T w[SIZE][SIZE];
    T lx[SIZE], ly[SIZE], slack[SIZE];
    int mx[SIZE], my[SIZE];
    bool vx[SIZE], vy[SIZE];
    KM() {}
    KM (int n) : n (n) {
        FOR (i, 1, n) fill (w[i], w[i] + n + 1, 0);
    }
    void add (int a, int b, T tw) {
        w[a][b] = max (w[a][b], tw);
    }
    bool dfs (int x, bool is) {
        if (vx[x]) return 0;
        vx[x] = 1;
        FOR (y, 1, n) {
            if (vy[y]) continue;
            T delta = lx[x] + ly[y] - w[x][y];
            if (delta == 0) {
                vy[y] = 1;
                if (my[y] == 0 || dfs (my[y], is)) {
                    if (is) my[mx[x] = y] = x;
                    return 1;
                }
            } else {
                slack[y] = min (slack[y], delta);
            }
        }
        return 0;
    }
    bool aug() {
        FOR (y, 1, n) {
            if (vy[y] == 0 && slack[y] == 0) {
                vy[y] = 1;
                if (my[y] == 0 || dfs (my[y], 0)) return 1;
            }
        }
        return 0;
    }
    void relabel() {
        T delta = INF;
        FOR (y, 1, n) if (vy[y] == 0) delta = min (delta, slack[y]);
        FOR (x, 1, n) if (vx[x]) lx[x] -= delta;
        FOR (y, 1, n) {
            if (vy[y]) ly[y] += delta;
            else slack[y] -= delta;
        }
    }
    U deal() {
        FOR (i, 1, n) {
            lx[i] = ly[i] = 0;
            mx[i] = my[i] = 0;
            FOR (j, 1, n) lx[i] = max (lx[i], w[i][j]);
        }
        FOR (i, 1, n) {
            FOR (j, 1, n) {
                vx[j] = vy[j] = 0;
                slack[j] = INF;
            }
            if (dfs (i, 1)) continue;
            while (aug() == 0) relabel();
            FOR (j, 1, n) vx[j] = vy[j] = 0;
            dfs (i, 1);
        }
        U ans = 0;
        FOR (y, 1, n) if (my[y]) ans += w[my[y]][y];
        return ans;
    }
};
