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
    std::vector<Edge> e;
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
                int to = e[i].to;
                T c = e[i].cap;
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
            int to = e[j].to;
            T c = e[j].cap;

            if (dep[to] == dep[node] + 1 &&
                (f = dfs(to, t, std::min(flow, c)))) {
                res += f;
                flow -= f;
                e[j].cap -= f;
                e[j ^ 1].cap += f;
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
    void add_edge(int u, int v, T c) {
        adj[u].push_back(e.size());
        e.emplace_back(v, c);
        adj[v].push_back(e.size());
        e.emplace_back(u, 0);
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
