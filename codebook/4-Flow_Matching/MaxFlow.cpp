template<typename Cap = int, typename Flow = long long>
struct MaxFlow {
    const static Cap INF = numeric_limits<Cap>::max();
    struct Edge {
        int a, b;
        Cap cap = 0, flow = 0;
        Edge() {}
        Edge(int a, int b, Cap cap) : a(a), b(b), cap(cap) {}
    };
    int n, m, s, t;
    Flow flow;
    vector<int> level, ptr;
    vector<Edge> e;
    vector<vector<int>> adj;
    MaxFlow() {}
    MaxFlow(int n, int s, int t) : n(n), s(s), t(t) {
        level = ptr = vector<int>(n + 1, 0);
        m = flow = 0, e.clear();
        adj = vector<vector<int>>(n + 1, vector<int>());
    }
    void add(int a, int b, Cap cap) {
        e.emplace_back(a, b, cap);
        e.emplace_back(b, a, 0);
        adj[a].emplace_back(m++);
        adj[b].emplace_back(m++);
    }
    bool bfs() {
        fill(level.begin(), level.end(), 0);
        fill(ptr.begin(), ptr.end(), 0);
        queue<int> q;
        level[s] = 1;
        q.push(s);
        while (q.size()) {
            int pos = q.front();
            q.pop();
            for (int id : adj[pos]) {
                auto &[a, b, cap, flow] = e[id];
                if (cap <= flow || level[b] != 0) {
                    continue;
                }
                level[b] = level[pos] + 1;
                q.push(b);
            }
        }
        return level[t] != 0;
    }
    Cap dfs(int pos, Cap mn = INF) {
        if (mn == 0 || pos == t) {
            return mn;
        }
        for (int &i = ptr[pos]; i < adj[pos].size(); i++) {
            int id = adj[pos][i];
            auto &[a, np, cap, flow] = e[id];
            if (level[np] != level[pos] + 1 || cap <= flow) {
                continue;
            }
            Cap val = dfs(np, min(mn, cap - flow));
            if (val == 0) {
                continue;
            }
            flow += val;
            e[id ^ 1].flow -= val;
            return val;
        }
        return 0;
    }
    void work() {
        while (bfs()) {
            while (1) {
                Cap val = dfs(s);
                flow += val;
                if (val == 0) {
                    break;
                }
            }
        }
    }
};
