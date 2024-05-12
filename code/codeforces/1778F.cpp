#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 1e5 + 19, MAXV = 1e3 + 19;

int n, k, a[MAXN];
std::vector<int> G[MAXN];
int g[MAXN];

void dfs1(int node, int f) {
    g[node] = a[node];
    for (int to : G[node]) {
        if (to == f)
            continue;
        dfs1(to, node);
        g[node] = std::gcd(g[node], g[to]);
    }
}

int dp[MAXN][MAXV], rt[MAXV];
std::vector<int> d;
void dfs(int node, int f) {
    for (int to : G[node]) {
        if (to == f)
            continue;
        dfs(to, node);
    }

    static int g[MAXV];
    for (int v : d) {
        g[v] = 0;
    }
    for (int to : G[node]) {
        if (to == f)
            continue;
        for (int v : d) {
            g[v] += dp[to][rt[v]];
        }
    }
    for (int v : d) {
        if (a[node] * a[node] % v == 0) {
            dp[node][v] = g[v] + 1;
        } else {
            dp[node][v] = k + 1;
        }
    }

    for (int v : d) {
        g[v] = 0;
    }
    for (int to : G[node]) {
        if (to == f)
            continue;
        for (int v : d) {
            g[v] += dp[to][v];
        }
    }
    for (int v : d) {
        if (a[node] % v == 0) {
            dp[node][v] = std::min(dp[node][v], g[v]);
        }
    }
}

void solve() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        G[i].clear();
    }
    for (int i = 2; i <= n; ++i) {
        int u, v;
        std::cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    d.clear();
    for (int i = 1; i <= a[1]; ++i) {
        if (a[1] % i == 0) {
            d.push_back(i);
        }
    }
    dfs1(1, 0);
    dfs(1, 0);
    int ans = a[1];

    for (int v : d) {
        int res = 1;
        for (int to : G[1]) {
            res += dp[to][v];
        }
        if (res <= k) {
            ans = std::max(ans, a[1] * v);
        }
    }

    std::cout << ans << '\n';
}

int main() {
    for (int i = 1; i < MAXV; ++i) {
        for (int j = 1; j <= i; ++j) {
            if (j * j % i == 0) {
                rt[i] = j;
                break;
            }
        }
    }

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}