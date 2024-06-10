#include <bits/stdc++.h>

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template <class Iter>
auto random_choice(Iter begin, Iter end) {
    int sz = end - begin;
    return *(begin + std::uniform_int_distribution<int>(0, sz - 1)(rng));
}

struct SegmentTree {
    struct Node {
        int min{0}, tag{0};
    };
    std::vector<Node> tr;
    SegmentTree(int n) : tr(n * 4 + 2) {}
    void push_up(int node) {
        tr[node].min =
            std::min(tr[node << 1].min, tr[node << 1 | 1].min) + tr[node].tag;
    }
    void modify(int node, int L, int R, int l, int r, const int &val) {
        if (l <= L && R <= r) {
            tr[node].min += val;
            tr[node].tag += val;
            return;
        }
        int mid = (L + R) / 2;
        if (l <= mid) {
            modify(node << 1, L, mid, l, r, val);
        }
        if (r > mid) {
            modify(node << 1 | 1, mid + 1, R, l, r, val);
        }
        push_up(node);
    }
    int operator()() const {
        return tr[1].min;
    }
};

struct DSU {
    std::vector<int> fa;
    DSU(int n) : fa(n) {
        std::iota(fa.begin(), fa.end(), 0);
    }
    int getf(int x) {
        return fa[x] == x ? x : fa[x] = getf(fa[x]);
    }
    void merge(int x, int y) {
        x = getf(x);
        y = getf(y);
        if (x != y) {
            fa[x] = y;
        }
    }
};

struct EdgeAbstration {
    int u, v;
    bool wu, wv;
    EdgeAbstration(std::pair<int, int> a = {}, std::pair<int, int> b = {}) {
        u = b.first;
        v = b.second;
        wu = (a.first == u || a.second == u);
        wv = (a.first == v || a.second == v);
    }
    void reverse() {
        std::swap(u, v);
        std::swap(wu, wv);
    }
};

void solve() {
    int n, m;
    std::cin >> n >> m;
    m = std::max(n, m);

    auto input = [&](std::vector<std::pair<int, int>> &a) {
        for (int i = 1; i <= n; ++i) {
            int k;
            std::cin >> k;

            std::cin >> a[i].first;
            if (k == 1) {
                a[i].second = a[i].first;
            } else {
                std::cin >> a[i].second;
            }
        }
    };

    std::vector<EdgeAbstration> b(n + 1);
    {
        std::vector<std::pair<int, int>> _a(n + 1), _b(n + 1);
        input(_a);
        input(_b);
        for (int i = 1; i <= n; ++i) {
            b[i] = EdgeAbstration{_a[i], _b[i]};
        }
    }

    DSU dsu{m + 1};
    for (int i = 1; i <= n; ++i) {
        dsu.merge(b[i].u, b[i].v);
    }

    std::vector<std::vector<int>> vertex(m + 1), edge(m + 1);
    for (int i = 1; i <= n; ++i) {
        int x = dsu.getf(b[i].u);
        edge[x].push_back(i);
    }
    for (int i = 1; i <= m; ++i) {
        int x = dsu.getf(i);
        vertex[x].push_back(i);
    }

    for (int i = 1; i <= m; ++i) {
        if (edge[i].size() > vertex[i].size()) {
            std::cout << "-1\n";
            return;
        }
    }

    std::vector<std::vector<int>> adj(m + 1);
    for (int i = 1; i <= n; ++i) {
        adj[b[i].u].push_back(i);
        adj[b[i].v].push_back(i);
    }

    std::vector<uint8_t> e_vist(n + 1), v_vist(m + 1), vist(m + 1);
    std::vector<int> cyc(m + 1);
    auto solve_pseudotree = [&](int _) -> int {
        const int rt = random_choice(vertex[_].begin(), vertex[_].end());

        std::vector<int> stk;
        int cyc_len = 0;
        auto dfs = [&](auto self, int node) -> bool {
            v_vist[node] = true;
            stk.push_back(node);
            for (int t : adj[node]) {
                if (!e_vist[t]) {
                    int to = b[t].u + b[t].v - node;
                    if (!v_vist[to]) {
                        e_vist[t] = true;
                        if (self(self, to)) {
                            return true;
                        }
                        e_vist[t] = false;
                    } else {
                        while (stk.back() != to) {
                            cyc[stk.back()] = ++cyc_len;
                            stk.pop_back();
                        }
                        cyc[to] = ++cyc_len;
                        return true;
                    }
                }
            }
            stk.pop_back();
            return false;
        };
        assert(dfs(dfs, rt));

        std::array<int, 2> f{};
        int alt = 0, all = 0;

        auto work = [&](auto self, int node) -> void {
            vist[node] = true;
            for (int t : adj[node]) {
                int to = b[t].u + b[t].v - node;
                if (b[t].u != to) {
                    b[t].reverse();
                }
                if (!vist[to] && !cyc[to]) {
                    // std::cerr << "b_" << t << " must be " << to << '\n';
                    if (b[t].wu) {
                        all += 1;
                        // std::cerr << "and a_" << t << " can be the same\n";
                    }
                    self(self, to);
                }
            }
        };
        for (int i : vertex[_]) {
            if (cyc[i]) {
                work(work, i);
            }
        }

        if (cyc_len == 2) {
            std::vector<int> cycle;
            for (int i : edge[_]) {
                if (cyc[b[i].u] && cyc[b[i].v]) {
                    cycle.push_back(i);
                }
            }
            int x = cycle[0], y = cycle[1];
            if (b[x].u == b[y].u) {
                b[y].reverse();
            }
        } else {
            for (int i : edge[_]) {
                if (cyc[b[i].u] && cyc[b[i].v]) {
                    if ((cyc[b[i].v] - cyc[b[i].u] + cyc_len) % cyc_len != 1) {
                        b[i].reverse();
                    }
                }
            }
        }
        for (int i : edge[_]) {
            if (cyc[b[i].u] && cyc[b[i].v]) {
                if (b[i].u == b[i].v && b[i].wu) {
                    ++all;
                } else if (b[i].wu && b[i].wv) {
                    ++alt;
                } else if (b[i].wu) {
                    ++f[0];
                } else if (b[i].wv) {
                    ++f[1];
                }
            }
        }

        if (f[0] > f[1]) {
            std::swap(f[0], f[1]);
        }
        if (f[0] + alt <= f[1]) {
            return f[0] + alt + all;
        }
        return (f[0] + f[1] + alt) / 2 + all;
    };

    std::vector<int> dfn(m + 1), size(m + 1);
    auto solve_tree = [&](int _) -> int {
        const int sz = vertex[_].size();
        SegmentTree mt{sz};

        const int rt = random_choice(vertex[_].begin(), vertex[_].end());

        int ind = 0;
        auto dfs1 = [&](auto self, int node, int fa) -> void {
            size[node] = 1;
            dfn[node] = ++ind;
            for (int t : adj[node]) {
                int to = b[t].u + b[t].v - node;
                if (to == fa) {
                    continue;
                }

                self(self, to, node);
                size[node] += size[to];

                if (b[t].u != node) {
                    b[t].reverse();
                }
                if (b[t].wv) {
                    mt.modify(1, 1, sz, 1, sz, 1);
                    mt.modify(1, 1, sz, dfn[to], dfn[to] + size[to] - 1, -1);
                } else if (b[t].wu) {
                    mt.modify(1, 1, sz, dfn[to], dfn[to] + size[to] - 1, 1);
                }
            }
        };
        dfs1(dfs1, rt, 0);

        int ans = 0;
        auto dfs2 = [&](auto self, int node, int fa) -> void {
            ans = std::max(ans, mt());
            for (int t : adj[node]) {
                int to = b[t].u + b[t].v - node;
                if (to == fa) {
                    continue;
                }

                if (b[t].wu && b[t].wv) {
                    mt.modify(1, 1, sz, 1, sz, -1);
                    mt.modify(1, 1, sz, dfn[to], dfn[to] + size[to] - 1, 2);

                    self(self, to, node);

                    mt.modify(1, 1, sz, 1, sz, 1);
                    mt.modify(1, 1, sz, dfn[to], dfn[to] + size[to] - 1, -2);
                } else {
                    self(self, to, node);
                }
            }
        };
        dfs2(dfs2, rt, 0);

        return ans;
    };

    int ans = 0;
    for (int _ = 1; _ <= m; ++_) {
        if (vertex[_].size() == 0) {
            continue;
        }
        int v;
        if (vertex[_].size() == edge[_].size()) {
            ans += (v = solve_pseudotree(_));
            // std::cerr << "A pseudo tree: ";
            // for (int i : vertex[_]) {
            //     std::cerr << i << ' ';
            // }
            // std::cerr << '\n';
            // std::cerr << "edge:\n";
            // for (int i : edge[_]) {
            //     std::cerr << std::format("{}({}) {}({})\n", b[i].u,
            //                              int(b[i].wu), b[i].v, int(b[i].wv));
            // }
            // std::cerr << "value = " << v << '\n';
            // std::cerr << '\n';
        } else {
            ans += (v = solve_tree(_));
            // std::cerr << "A tree: ";
            // for (int i : vertex[_]) {
            //     std::cerr << i << ' ';
            // }
            // std::cerr << '\n';
            // std::cerr << "edge:\n";
            // for (int i : edge[_]) {
            //     std::cerr << std::format("{}({}) {}({})\n", b[i].u,
            //                              int(b[i].wu), b[i].v, int(b[i].wv));
            // }
            // std::cerr << "value = " << v << '\n';
            // std::cerr << '\n';
        }
    }

    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}