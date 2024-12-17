#include <bits/stdc++.h>

struct SCC {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> stk;
    std::vector<int> dfn, low, bel;
    int cur, cnt;
    void dfs(int x, int p) {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);

        bool skipped = false;
        for (int to : adj[x]) {
            if (to == p && !skipped) {
                skipped = true;
                continue;
            }
            if (dfn[to] == -1) {
                dfs(to, x);
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
        : n(n), adj(n), dfn(n, -1), low(n), bel(n, -1), cur(0), cnt(0) {};

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<int> operator()() {
        for (int i = 0; i < n; ++i)
            if (dfn[i] == -1) dfs(i, -1);
        return bel;
    }
};

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::pair<int, int>> edge(m);
    for (auto &[u, v] : edge) {
        std::cin >> u >> v;
        --u, --v;
    }

    std::vector<int> a(n);
    for (int &i : a) std::cin >> i;

    if (std::unordered_set<int>{a.begin(), a.end()}.size() == 1) {
        std::cout << "Yes\n";
        std::copy(a.begin(), a.end(),
                  std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';
        return;
    }

    SCC _g(n);
    for (auto [u, v] : edge) _g.add_edge(u, v);
    auto bel = _g();

    const int N = *std::max_element(bel.begin(), bel.end()) + 1;
    std::vector<std::vector<int>> adj(N);
    for (auto [u, v] : edge) {
        if (bel[u] != bel[v]) {
            adj[bel[u]].push_back(bel[v]);
            adj[bel[v]].push_back(bel[u]);
        }
    }
    std::vector<std::vector<int>> com(N);
    for (int i = 0; i < n; ++i) com[bel[i]].push_back(i);

    // Discretize
    std::vector<int> tmp(a);
    std::sort(tmp.begin(), tmp.end());
    tmp.resize(std::unique(tmp.begin(), tmp.end()) - tmp.begin());

    // Count of each value
    std::vector<int> cnt(tmp.size());
    for (int &i : a)
        cnt[std::lower_bound(tmp.begin(), tmp.end(), i) - tmp.begin()]++;

    std::vector<int> presum(tmp.size());
    std::partial_sum(cnt.begin(), cnt.end(), presum.begin());

    std::unordered_set<int> S;
    for (int i = 0; i + 1 < tmp.size(); ++i) S.insert(n - 2 * presum[i]);

    int rt = 19 % N; // Just a random root

    std::vector<int> sz(N);
    std::vector<int> f(N), g(N);

    auto F = [&](int x) { return S.find(n - 2 * sz[x]) != S.end(); };
    auto G = [&](int x) { return S.find(2 * sz[x] - n) != S.end(); };

    auto dfs = [&](auto &self, int x, int p) -> void {
        for (int to : adj[x]) {
            if (to == p) continue;
            self(self, to, x);
            sz[x] += sz[to];
            f[x] = std::max(f[x], f[to]);
            g[x] = std::max(g[x], g[to]);
        }
        sz[x] += com[x].size();
        if (F(x)) f[x] += 1;
        if (G(x)) g[x] += 1;
    };
    dfs(dfs, rt, -1);

    auto output = [&](int x, int y, int z) -> void {
        std::vector<int> col(N, -1);
        auto dfs1 = [&](auto &self, int x, int p, int c, auto &dp,
                        auto &&fn) -> void {
            col[x] = c;

            int son = -1;
            for (int to : adj[x]) {
                if (to == p) continue;
                if (son == -1 || dp[son] < dp[to]) son = to;
            }

            if (son != -1) self(self, son, x, c - fn(son), dp, fn);
        };

        int c = x != -1 ? f[x] : tmp.size() - 1 - g[z];

        col[y] = c;
        if (x != -1) dfs1(dfs1, x, y, c - F(x), f, F);
        if (z != -1)
            dfs1(dfs1, z, y, c + G(z), g, [&](int x) { return -G(x); });

        auto dfs2 = [&](auto &self, int x, int p) -> void {
            for (int to : adj[x]) {
                if (to == p) continue;
                if (col[to] == -1) col[to] = col[x];
                self(self, to, x);
            }
        };
        dfs2(dfs2, y, -1);

        for (int i = 0; i < n; ++i) a[i] = tmp[col[bel[i]]];

        std::cout << "Yes\n";
        std::copy(a.begin(), a.end(),
                  std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';
    };

    auto check = [&](int x) -> bool {
        int pf = -1, pg = -1;
        for (int to : adj[x]) {
            if (sz[to] > sz[x]) continue;
            if (pf != -1 && f[pf] + g[to] >= tmp.size() - 1) {
                output(pf, x, to);
                return true;
            }
            if (pg != -1 && f[to] + g[pg] >= tmp.size() - 1) {
                output(to, x, pg);
                return true;
            }
            if (pf == -1 || f[to] > f[pf]) pf = to;
            if (pg == -1 || g[to] > g[pg]) pg = to;

            if (f[to] >= tmp.size() - 1) {
                output(to, x, -1);
                return true;
            }
            if (g[to] >= tmp.size() - 1) {
                output(-1, x, to);
                return true;
            }
        }
        return false;
    };

    for (int i = 0; i < N; ++i)
        if (check(i)) return;
    std::cout << "No\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) solve();
}
