#ifdef ONLINE_JUDGE
#include <bits/stdc++.h>
#endif

#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

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
    T operator()(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, INF);
            if (ans > INF) {
                return INF;
            }
        }
        return ans;
    }
};

using real = long double;
constexpr int INF = 1e9;

void solve() {
    int n, m, p, y;
    std::cin >> n >> m >> p >> y;

    std::vector<int> c(p);
    for (int i = 0; i < p; ++i) {
        std::cin >> c[i];
    }

    std::vector<std::vector<real>> bonus(m, std::vector<real>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            real ok = 1;
            for (int k = 0; k < p; ++k) {
                real prob;
                std::cin >> prob;
                ok *= prob;
                bonus[i][j] += c[k] * ok;
            }
        }
    }

    Flow<real> f{n * m + 2};
    const int s = n * m, t = n * m + 1;
    auto coord = [&](int x, int y) {
        if (y >= m) {
            return t;
        }
        return x * m + y;
    };

    for (int i = 0; i < n; ++i) {
        f.add_edge(s, coord(i, 0), INF);
        for (int j = 0; j < m; ++j) {
            f.add_edge(coord(i, j), coord(i, j + 1), bonus[j][i]);
        }
    }

    for (int _ = 0; _ < y; ++_) {
        int x, y, k;
        std::cin >> x >> y >> k;
        --x, --y;
        for (int i = std::max(0, -k); i < m; ++i) {
            f.add_edge(coord(y, i), coord(x, std::min(i + k, m)), INF);
        }
    }

    real ans = f(s, t);
    if (ans == INF) {
        std::cout << "-1\n";
    } else {
        std::cout << std::fixed << std::setprecision(8);
        std::cout << ans << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
}
