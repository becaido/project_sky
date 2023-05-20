template<typename Cap = int, typename Flow = long long, typename Cost = int, typename Sum = long long>
struct MinCostMaxFlow {
    const static Sum INF = numeric_limits<Sum>::max();
    struct Edge {
        int a, b;
        Cap cap;
        Cost cost;
        Edge() {}
        Edge(int a, int b, Cap cap, Cost cost) : a(a), b(b), cap(cap), cost(cost) {}
    };
    int n, m, s, t;
    Flow flow;
    Sum sum;
    vector<vector<int>> adj;
    vector<Edge> e;
    vector<Sum> dis;
    vector<int> pre, inq;
    MinCostMaxFlow() {}
    MinCostMaxFlow(int n, int s, int t) : n(n), s(s), t(t) {
        m = flow = sum = 0;
        adj = vector<vector<int>>(n + 1, vector<int>());
        e.clear();
        dis = vector<Sum>(n + 1, 0);
        pre = inq = vector<int>(n + 1, 0);
    }
    void add(int a, int b, Cap cap, Cost cost) {
        e.emplace_back(a, b, cap, cost);
        e.emplace_back(b, a, 0, -cost);
        adj[a].emplace_back(m++);
        adj[b].emplace_back(m++);
    }
    void spfa() {
        fill(inq.begin(), inq.end(), 0);
        fill(pre.begin(), pre.end(), 0);
        for (auto &x : dis) x = INF;
        queue<int> q;
        dis[s] = 0;
        q.push(s);
        while (q.size()) {
            int pos = q.front();
            q.pop();
            inq[pos] = 0;
            for (int id : adj[pos]) {
                auto &[a, b, cap, cost] = e[id];
                if (cap > 0 && dis[pos] + cost < dis[b]) {
                    dis[b] = dis[pos] + cost;
                    pre[b] = id;
                    if (inq[b] == 0) {
                        inq[b] = 1;
                        q.push(b);
                    }
                }
            }
        }
    }
    void work(Flow lim = numeric_limits<Flow>::max()) {
        while (flow < lim) {
            spfa();
            if (dis[t] == INF) {
                break;
            }
            Cap mn = min((Flow) numeric_limits<Cap>::max(), lim - flow);
            int pos = t;
            while (pos != s) {
                int id = pre[pos];
                mn = min(mn, e[id].cap);
                pos = e[id].a;
            }
            flow += mn;
            sum += dis[t] * mn;
            pos = t;
            while (pos != s) {
                int id = pre[pos];
                e[id].cap -= mn;
                e[id ^ 1].cap += mn;
                pos = e[id].a;
            }
        }
    }
};
