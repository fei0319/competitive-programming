#ifdef ONLINE_JUDGE
#include <bits/stdc++.h>
#endif
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
        }
        return ans;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::pair<std::pair<int, int>, int>> edges(m);
    for (auto &edge : edges) {
        std::cin >> edge.first.first >> edge.first.second >> edge.second;
    }

    int s, t, w;
    std::cin >> s >> t >> w;

    Flow<int> f{n + 1}, g{n + 1};
    for (const auto &edge : edges) {
        if (edge.second < w) {
            f.add_edge(edge.first.first, edge.first.second, 1);
            f.add_edge(edge.first.second, edge.first.first, 1);
        } else if (edge.second > w) {
            g.add_edge(edge.first.first, edge.first.second, 1);
            g.add_edge(edge.first.second, edge.first.first, 1);
        }
    }

    std::cout << f(s, t) + g(s, t) << '\n';
}
