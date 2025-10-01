#include <iostream>
#include <iterator>
#include <queue>
#include <unordered_set>
#include <vector>

template <typename T>
struct Flow {
    int n;
    struct Edge {
        int to;
        T cap;
        Edge(int to, T cap) : to(to), cap(cap) {}
    };
    std::vector<Edge> edge;
    std::vector<std::vector<int>> adj;
    std::vector<int> cur, dep;
    explicit Flow(int n) : n(n), adj(n) {}
    bool bfs(int s, int t) {
        dep.assign(n, -1);
        std::queue<int> q;
        dep[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (int i : adj[node]) {
                int to = edge[i].to;
                T c = edge[i].cap;
                if (c > 0 && dep[to] == -1) {
                    dep[to] = dep[node] + 1;
                    if (to == t) return true;
                    q.push(to);
                }
            }
        }
        return false;
    }
    T dfs(int node, int t, T flow) {
        if (node == t || flow == 0) return flow;
        T f, res = 0;
        for (int &i = cur[node]; i < int(adj[node].size()); ++i) {
            int j = adj[node][i], to = edge[j].to;
            T c = edge[j].cap;
            if (dep[to] == dep[node] + 1 &&
                (f = dfs(to, t, std::min(flow, c)))) {
                res += f, flow -= f;
                edge[j].cap -= f, edge[j ^ 1].cap += f;
            }
            if (flow == 0) break;
        }
        if (!res) dep[node] = -1;
        return res;
    }
    int add_edge(int u, int v, T c) {
        int j = edge.size();
        adj[u].push_back(edge.size());
        edge.emplace_back(v, c);
        adj[v].push_back(edge.size());
        edge.emplace_back(u, 0);
        return j;
    }
    T operator()(int s, int t, const T INF = 1e9) {
        T ans = 0;
        while (bfs(s, t)) cur.assign(n, 0), ans += dfs(s, t, INF);
        return ans;
    }
};

struct SCC {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> stk;
    std::vector<int> dfn, low, bel;
    int cur, cnt;
    void dfs(int x) {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);
        for (int to : adj[x]) {
            if (dfn[to] == -1) {
                dfs(to);
                low[x] = std::min(low[x], low[to]);
            } else if (bel[to] == -1) {
                low[x] = std::min(low[x], dfn[to]);
            }
        }
        if (dfn[x] == low[x]) {
            int y;
            do {
                y = stk.back();
                bel[y] = cnt;
                stk.pop_back();
            } while (y != x);
            ++cnt;
        }
    }

public:
    explicit SCC(int n)
        : n(n), adj(n), dfn(n, -1), low(n), bel(n, -1), cur(0), cnt(0) {}

    void add_edge(int u, int v) { adj[u].push_back(v); }
    std::vector<int> operator()() {
        for (int i = 0; i < n; i++)
            if (dfn[i] == -1) dfs(i);
        return bel;
    }
};

void solve() {
    int n, m, t;
    std::cin >> n >> m >> t;

    std::vector<std::pair<int, int>> edge_list(t);
    for (auto &[u, v] : edge_list) {
        std::cin >> u >> v;
        --u, --v;
    }

    auto f = Flow<int>(n + m + 2);
    for (const auto [u, v] : edge_list) {
        f.add_edge(u, n + v, 1);
    }
    for (int i = 0; i < n; ++i) f.add_edge(n + m, i, 1);
    for (int i = 0; i < m; ++i) f.add_edge(n + i, n + m + 1, 1);
    f(n + m, n + m + 1);

    auto b = SCC(f.n);
    std::unordered_set<int> matching;
    for (int u = 0; u < f.n; ++u) {
        for (int id : f.adj[u]) {
            auto [v, cap] = f.edge[id];
            if (cap) {
                // std::cout << u << ' ' << v << '\n';
                b.add_edge(u, v);
            }
            if (u < n && v < n + m && !cap) {
                matching.insert(u * m + v - n);
            }
        }
    }
    auto bel = b();

    std::vector<int> ans;
    for (int i = 0; i < t; ++i) {
        auto [u, v] = edge_list[i];
        if (bel[u] != bel[n + v] && !matching.contains(u * m + v)) {
            ans.push_back(i + 1);
        }
    }

    std::cout << ans.size() << '\n';
    std::copy(ans.begin(), ans.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();
}
