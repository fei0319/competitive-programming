#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19, mod = 1e9 + 7;

int n, m, h, p[maxn << 1];
std::vector<std::pair<int, int>> G[maxn];

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = (ll)res * a % mod;
        a = (ll)a * a % mod, b >>= 1;
    }
    return res;
}

bool dfs(int node) {
    for (auto [to, v] : G[node])
        if (p[to] == -1) {
            p[to] = ((p[node] + v) % h + h) % h;
            if (!dfs(to)) return false;
        } else {
            if (p[to] != ((p[node] + v) % h + h) % h) return false;
        }
    return true;
}

void solve(void) {
    std::cin >> n >> m >> h;
    for (int i = 1; i <= n + m; ++i) G[i].clear();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            int v;
            std::cin >> v;
            if (v != -1) {
                G[i].emplace_back(n + j, v);
                G[n + j].emplace_back(i, -v);
            }
        }
    for (int i = 1; i <= n + m; ++i) p[i] = -1;
    int ans = qpow(h, mod - 2);
    for (int i = 1; i <= n + m; ++i)
        if (p[i] == -1) p[i] = 0, ans = (ll)ans * (dfs(i) ? h : 0) % mod;
    std::cout << ans << std::endl;
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