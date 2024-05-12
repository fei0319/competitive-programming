#include <bits/stdc++.h>

template <class T>
struct Flow {
    static constexpr int INF = 1e9;
    int n;
    struct Edge {
        int to;
        T cap;
        Edge(int to, T cap) : to(to), cap(cap) {}
    };
    std::vector<Edge> edge;
    std::vector<std::vector<int>> adj;
    std::vector<int> cur, dep;
    Flow(int n) : n(n), adj(n) {}
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
                    if (to == t) {
                        return true;
                    }
                    q.push(to);
                }
            }
        }
        return false;
    }
    T dfs(int node, int t, T flow) {
        if (node == t || flow == 0) {
            return flow;
        }
        T f, res = 0;
        for (int &i = cur[node]; i < int(adj[node].size()); ++i) {
            int j = adj[node][i];
            int to = edge[j].to;
            T c = edge[j].cap;

            if (dep[to] == dep[node] + 1 &&
                (f = dfs(to, t, std::min(flow, c)))) {
                res += f;
                flow -= f;
                edge[j].cap -= f;
                edge[j ^ 1].cap += f;
            }

            if (flow == 0) {
                break;
            }
        }
        if (!res) {
            dep[node] = -1;
        }
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
    T max_flow(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, INF);
        }
        return ans;
    }
};

void solve() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> a(n + 1, std::vector<int>(n + 1));
    std::vector<std::vector<int>> b(n + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cin >> a[i][j];
        }
        b[i].resize(n + 1);
        std::iota(b[i].begin(), b[i].end(), 0);
    }

    for (int col = 1; col <= n; ++col) {
        Flow<int> flow(n * 2 + 3);
        std::map<std::pair<int, int>, int> id;
        const int s = n * 2 + 1, t = n * 2 + 2;
        for (int i = 1; i <= n; ++i) {
            flow.add_edge(s, i, 1);
            flow.add_edge(i + n, t, 1);
        }
        for (int row = 1; row <= n; ++row) {
            std::set<int> s;
            for (int i = col; i <= n; ++i) {
                s.insert(a[row][i]);
            }
            for (int i : s) {
                id[{row, i}] = flow.add_edge(row, i + n, 1);
            }
        }
        assert(flow.max_flow(s, t) == n);

        std::vector<int> front(n + 1);
        for (auto [key, val] : id) {
            if (flow.edge[val].cap == 0) {
                front[key.first] = key.second;
            }
        }
        for (int row = 1; row <= n; ++row) {
            int p = col;
            while (a[row][p] != front[row]) {
                ++p;
            }
            std::swap(a[row][col], a[row][p]);
            std::swap(b[row][col], b[row][p]);
        }
    }

    std::vector<std::array<int, 4>> ans;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            ans.push_back({i, b[i][j], j, b[j][i]});
        }
    }

    std::cout << ans.size() << '\n';
    for (auto [a, b, c, d] : ans) {
        std::cout << std::format("{} {} {} {}\n", a, b, c, d);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}