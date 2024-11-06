#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 1e3 + 19;

int n, m, t[MAXN];

namespace Flow {
    const int MAXN = 2e3 + 19, MAXM = 1e6 + 19;
    const int INF = 1e9;
    struct Edge {
        int to, next;
        int capacity, flow;
    } edge[MAXM];
    int head[MAXN], cnt;

    int S, T, n;
    void init(int n) {
        Flow::n = n;
        std::fill(head, head + n + 1, -1);
        cnt = -1;
    }

    void add_directed(int from, int to, int capacity) {
        edge[++cnt] = Edge{to, head[from], capacity, 0};
        head[from] = cnt;
    }
    void add(int from, int to, int capacity) {
        add_directed(from, to, capacity);
        add_directed(to, from, 0);
    }

    int cur[MAXN], dep[MAXN];
    bool bfs() {
        std::fill(dep, dep + n + 1, 0);

        static int q[MAXN], h, t;
        q[h = t = 0] = S, dep[S] = 1;
        while (h <= t) {
            int node = q[h++];
            for (int i = head[node]; ~i; i = edge[i].next) {
                int to = edge[i].to;
                if (dep[to] || edge[i].capacity == edge[i].flow) {
                    continue;
                }
                dep[to] = dep[node] + 1;
                q[++t] = to;
            }
        }
        return dep[T];
    }
    int dfs(int node, int flow) {
        if (node == T || !flow) {
            return flow;
        }

        int res = 0;
        for (int &i = cur[node]; ~i; i = edge[i].next) {
            int to = edge[i].to, f;
            if (dep[to] == dep[node] + 1 &&
                (f = dfs(to, std::min(flow - res,
                                      edge[i].capacity - edge[i].flow)))) {
                res += f;
                edge[i].flow += f;
                edge[i ^ 1].flow -= f;
                if (res == flow) {
                    break;
                }
            }
        }
        return res;
    }

    ll max_flow() {
        ll res = 0;
        while (bfs()) {
            std::copy(head, head + n + 1, cur);
            res += dfs(S, INF);
        }
        return res;
    }
}; // namespace Flow

std::pair<int, int> construct_from(int x) { return {2 * x, 3 * x}; }
std::pair<int, int> construct_from(int a, int d) {
    return {a + d, a * 2 + d};
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> t[i];
    }

    std::vector<int> f, g;
    for (int i = 1; i <= n; ++i) {
        if (t[i] * 3LL <= m) {
            f.push_back(i);
        } else {
            g.push_back(i);
        }
    }

    Flow::S = n + 1, Flow::T = n + 2;
    Flow::init(n + 2);
    for (int i : f) {
        Flow::add(Flow::S, i, 1);
    }
    for (int i : g) {
        Flow::add(i, Flow::T, 1);
    }
    for (int u : f) {
        for (int v : g) {
            if (t[v] % t[u] == 0 && 2LL * t[v] + t[u] <= m) {
                Flow::add(u, v, 1);
            }
        }
    }

    if (Flow::max_flow() < g.size()) {
        std::cout << "-1\n";
        return 0;
    }

    std::multiset<int> s;
    for (int i : f) {
        s.insert(t[i]);
    }

    std::vector<std::pair<int, int>> ans;

    for (int x : g) {
        using namespace Flow;
        for (int i = head[x]; ~i; i = edge[i].next) {
            if (edge[i].to != T && edge[i].flow == -1) {
                ans.emplace_back(construct_from(t[x], t[edge[i].to]));
                s.erase(s.find(t[edge[i].to]));
                break;
            }
        }
    }
    for (int i : s) {
        ans.emplace_back(construct_from(i));
    }

    std::cout << ans.size() << '\n';
    for (auto [x, y] : ans) {
        std::cout << x << ' ' << y << '\n';
    }

    return 0;
}