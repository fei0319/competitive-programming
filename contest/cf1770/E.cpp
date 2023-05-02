#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 3e5 + 19, mod = 998244353;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1)
            res = (ll)res * a % mod;
        a = (ll)a * a % mod, b >>= 1;
    }
    return res;
}

int n, k, a[maxn], u[maxn], v[maxn], p[maxn], sz[maxn], dep[maxn];
std::vector<int> G[maxn];

void dfs(int node, int f) {
    dep[node] = dep[f] + 1;
    for (int to : G[node]) {
        if (to == f)
            continue;
        dfs(to, node);
        sz[node] += sz[to];
    }
}

int calc(int x) { return (ll)x * (k - x) % mod; }

void solve(void) {
    std::cin >> n >> k;
    for (int i = 1; i <= k; ++i)
        std::cin >> a[i];
    for (int i = 1; i < n; ++i) {
        std::cin >> u[i] >> v[i];
        G[u[i]].push_back(v[i]), G[v[i]].push_back(u[i]);
    }

    for (int i = 1; i <= n; ++i)
        sz[i] = 0, p[i] = 0;
    for (int i = 1; i <= k; ++i)
        sz[a[i]] = 1, p[a[i]] = 1;
    dfs(1, 0);

    int ans = 0, half = qpow(2, mod - 2);
    for (int i = 1; i < n; ++i) {
        // ensure u is father
        if (dep[u[i]] > dep[v[i]])
            std::swap(u[i], v[i]);
        int
            // u to v
            p1 = (ll)p[u[i]] * (1 - p[v[i]]) % mod * half % mod,
            // v to u
            p2 = (ll)p[v[i]] * (1 - p[u[i]]) % mod * half % mod,
            // else
            p3 = (1 - p1 - p2) % mod;

        ans = (ans + (ll)p1 * calc(sz[v[i]] + 1) + (ll)p2 * calc(sz[v[i]] - 1) +
               (ll)p3 * calc(sz[v[i]])) %
              mod;

        int pu = p[u[i]], pv = p[v[i]];
        p[u[i]] = ((ll)pu * (pv + ll(1 - pv) * half % mod) +
                   ll(1 - pu) * pv % mod * half % mod) %
                  mod;
        p[v[i]] = ((ll)pv * (pu + ll(1 - pu) * half % mod) +
                   ll(1 - pv) * pu % mod * half % mod) %
                  mod;
    }

    ans = (ll)ans * qpow((ll)k * (k - 1) / 2 % mod, mod - 2) % mod;
    ans = (ans + mod) % mod;
    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T = 1;

    while (T--) {
        solve();
    }

    return 0;
}