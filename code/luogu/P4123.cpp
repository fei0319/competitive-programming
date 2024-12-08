#ifdef ONLINE_JUDGE
#include <bits/stdc++.h>
#endif
#include <iostream>
#include <numeric>
#include <queue>
#include <random>
#include <unordered_set>
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
    int n, m;
    std::cin >> n >> m;

    Flow<int> f{n};
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        --u, --v;
        f.add_edge(u, v, w);
        f.add_edge(v, u, w);
    }

    std::mt19937 rbg{(uint32_t)std::chrono::steady_clock::now()
                         .time_since_epoch()
                         .count()};

    std::unordered_set<int> ans;
    std::vector<int> a(n);
    std::iota(a.begin(), a.end(), 0);
    Flow<int> nf = f;
    auto solve = [&](auto self, int l, int r) -> void {
        if (l == r) {
            return;
        }

        int s = std::uniform_int_distribution<int>{l, r}(rbg), t = s;
        while (t == s) {
            t = std::uniform_int_distribution<int>{l, r}(rbg);
        }
        s = a[s], t = a[t];

        nf = f;
        ans.insert(nf(s, t));

        nf.bfs(s, t);
        std::sort(a.begin() + l, a.begin() + r + 1,
                  [&](int x, int y) { return nf.dep[x] < nf.dep[y]; });

        int mid = l;
        while (mid + 1 <= r && nf.dep[a[mid + 1]] == -1) {
            ++mid;
        }
        self(self, l, mid);
        self(self, mid + 1, r);
    };
    solve(solve, 0, n - 1);

    std::cout << ans.size() << '\n';
}
