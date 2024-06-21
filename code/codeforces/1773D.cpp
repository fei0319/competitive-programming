#ifdef ONLINE_JUDGE
#include <bits/stdc++.h>
#endif
#include <array>
#include <cstdint>
#include <iostream>
#include <queue>
#include <random>
#include <vector>

auto current_time() {
    return std::chrono::steady_clock::now();
}
std::mt19937 rng(current_time().time_since_epoch().count());

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
    void randomize() {
        for (int i = 0; i < n; ++i) {
            std::shuffle(adj[i].begin(), adj[i].end(), rng);
        }
    }
};

template <class T>
struct Counter {
    std::vector<std::vector<int>> adj;
    int n;
    explicit Counter(std::vector<std::vector<int>> adj)
        : adj(adj), n(adj.size()) {}
    T operator()() {
        std::vector<int> color(n, -1);
        int tot = 0;

        std::vector<int> dfn(n), low(n);
        std::vector<int> st;
        std::vector<uint8_t> instk(n);
        int ind = 0;

        auto dfs0 = [&](auto self, int node) -> void {
            dfn[node] = low[node] = ++ind;
            st.push_back(node);
            instk[node] = true;
            for (int to : adj[node]) {
                if (!dfn[to]) {
                    self(self, to);
                    low[node] = std::min(low[node], low[to]);
                } else if (instk[to]) {
                    low[node] = std::min(low[node], dfn[to]);
                }
            }
            if (dfn[node] == low[node]) {
                while (st.back() != node) {
                    color[st.back()] = tot;
                    instk[st.back()] = false;
                    st.pop_back();
                }
                color[st.back()] = tot;
                instk[st.back()] = false;
                st.pop_back();
                ++tot;
            }
        };

        for (int i = 0; i < n; ++i) {
            if (!adj[i].empty() && !dfn[i]) {
                dfs0(dfs0, i);
            }
        }

        std::vector<std::vector<int>> nadj(tot);
        std::vector<int> size(tot);
        for (int i = 0; i < n; ++i) {
            if (color[i] == -1) {
                continue;
            }

            size[color[i]] += 1;
            for (int to : adj[i]) {
                if (color[to] != color[i]) {
                    nadj[color[i]].push_back(color[to]);
                }
            }
        }

        std::vector<uint8_t> vist(tot);
        auto dfs1 = [&](auto self, int node) -> T {
            vist[node] = true;
            T res{size[node]};
            for (auto to : nadj[node]) {
                if (!vist[to]) {
                    res += self(self, to);
                }
            }
            return res;
        };
        T ans = 0;
        for (int i = 0; i < tot; ++i) {
            std::fill(vist.begin(), vist.end(), false);
            ans += T{size[i]} * dfs1(dfs1, i);
        }

        return ans;
    }
};

using i64 = int64_t;

constexpr int D = 4;
constexpr int DX[D] = {-1, 1, 0, 0};
constexpr int DY[D] = {0, 0, -1, 1};
constexpr int LIMIT = 1e6;

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> mp(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> mp[i];
    }

    i64 tot = 0;
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            if (mp[x][y] == '.') {
                tot += 1;
            }
        }
    }
    if (tot / 2 * (tot / 2 - 1) >= LIMIT) {
        std::cout << LIMIT << '\n';
        return 0;
    }

    auto encode = [&](int x, int y) {
        return m * x + y;
    };

    std::vector<uint8_t> type(n * m);
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            type[encode(x, y)] = (x & 1) ^ (y & 1);
        }
    }

    std::vector<std::vector<int>> adj(n * m);

    Flow<int> flow(n * m + 2);
    const int flow_s = n * m, flow_t = n * m + 1;

    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            if (mp[x][y] != '.') {
                continue;
            }
            int from = encode(x, y);

            if (type[from]) {
                flow.add_edge(flow_s, from, 1);
            } else {
                flow.add_edge(from, flow_t, 1);
            }

            for (int i = 0; i < D; ++i) {
                int to_x = x + DX[i], to_y = y + DY[i];
                int to = -1;
                if (to_x >= 0 && to_x < n && to_y >= 0 && to_y < m &&
                    mp[to_x][to_y] == '.') {
                    to = encode(to_x, to_y);
                }

                if (to != -1) {
                    adj[from].push_back(to);
                    if (type[from]) {
                        flow.add_edge(from, to, 1);
                    }
                }
            }
        }
    }

    std::vector<std::vector<int>> nadj(n * m);
    // for (auto s_time = current_time();
    //      std::chrono::duration_cast<std::chrono::milliseconds>(current_time()
    //      -
    //                                                            s_time)
    //          .count() < 2000;)
    {
        auto nflow = flow;
        nflow.randomize();
        assert(nflow(flow_s, flow_t) == tot / 2);
        std::vector<int> partner(n * m, -1);
        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < m; ++y) {
                if (mp[x][y] != '.') {
                    continue;
                }
                int now = encode(x, y);
                if (type[now]) {
                    for (int i : nflow.adj[now]) {
                        if (i % 2 == 0 && nflow.edge[i].cap == 0) {
                            partner[now] = nflow.edge[i].to;
                            break;
                        }
                    }
                    assert(partner[now] != -1);
                }
            }
        }

        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < m; ++y) {
                if (mp[x][y] != '.') {
                    continue;
                }
                int now = encode(x, y);
                if (type[now]) {
                    nadj[now].insert(nadj[now].end(), adj[partner[now]].begin(),
                                     adj[partner[now]].end());
                    auto unique = [](std::vector<int> &vec) {
                        std::sort(vec.begin(), vec.end());
                        vec.resize(std::unique(vec.begin(), vec.end()) -
                                   vec.begin());
                    };
                    unique(nadj[now]);
                }
            }
        }
    }

    // int x = 0;
    // for (int i = 0; i < n * m; ++i) {
    //     x += nadj[i].size();
    // }
    // std::cerr << x << '\n';

    i64 ans = Counter<i64>{nadj}();

    std::cout << std::min<i64>(tot * (tot - 1) / 2 - ans, LIMIT) << '\n';

    return 0;
}
