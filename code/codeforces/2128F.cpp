#include <bits/stdc++.h>

using i64 = int64_t;
template <typename T>
using minpq = std::priority_queue<T, std::vector<T>, std::greater<T>>;

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;
    --k;

    std::vector<std::vector<std::tuple<int, int, int>>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v, l, r;
        std::cin >> u >> v >> l >> r;
        --u, --v;
        adj[u].emplace_back(v, l, r);
        adj[v].emplace_back(u, l, r);
    }

    std::vector<i64> f(n, std::numeric_limits<i64>::max());
    {
        minpq<std::pair<i64, int>> q{};
        std::vector<uint64_t> vis(n, false);
        f[k] = 0;
        q.emplace(0, k);

        while (!q.empty()) {
            const auto [_, x] = q.top();
            q.pop();
            if (vis[x]) continue;
            vis[x] = true;

            for (const auto [to, l, r] : adj[x]) {
                const i64 v = f[x] + r;
                if (f[to] > v) {
                    f[to] = v;
                    q.emplace(f[to], to);
                }
            }
        }
    }

    // P[u,x]-f[u]-f[x]=max(P[v,x]-f[x]+d-f[u],d-f[u]-f[v])
    // P[u,x]-f[x]=max(P[v,x]-f[x],-f[v])+d
    // g[u]=max(g[v],-f[v])+d
    // g[u]-f[u]<0

    std::vector<i64> g(n, std::numeric_limits<i64>::max());
    {
        minpq<std::pair<i64, int>> q{};
        std::vector<uint8_t> vis(n, false);
        g[0] = -f[0];
        q.emplace(g[0], 0);

        while (!q.empty()) {
            const auto [_, x] = q.top();
            q.pop();
            if (vis[x]) continue;
            vis[x] = true;

            if (std::max(g[x], -f[x]) - f[x] >= 0) continue;

            for (const auto [to, l, r] : adj[x]) {
                const i64 v = std::max(g[x], -f[x]) + l;
                if (g[to] > v) {
                    g[to] = v;
                    q.emplace(std::max(g[to], -f[to]), to);
                }
            }
        }
    }

    if (g[n - 1] - f[n - 1] < 0) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) solve();
}
