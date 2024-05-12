#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 3e3 + 19, MOD = 998244353;

int n, deg[MAXN], dp[MAXN][MAXN];
std::vector<int> G[MAXN];
int fact[MAXN];

void dfs(int node, int f) {
    dp[node][0] = 1;
    deg[node] = 0;
    for (int to : G[node]) {
        if (to == f) {
            continue;
        }
        dfs(to, node);

        static int g[MAXN];

        for (int i = 0; i <= deg[node] + 1; ++i) {
            g[i] = 0;
        }
        for (int i = 1; i <= deg[node] + 1; ++i) {
            for (int j = 0; j <= deg[to]; ++j) {
                g[i] =
                    (g[i] + (ll)dp[node][i - 1] * dp[to][j] % MOD * (j + 1)) %
                    MOD;
            }
        }
        for (int i = 0; i <= deg[node]; ++i) {
            for (int j = 0; j <= deg[to]; ++j) {
                g[i] = (g[i] + (ll)dp[node][i] * dp[to][j]) % MOD;
            }
        }
        for (int i = 0; i <= deg[node] + 1; ++i) {
            dp[node][i] = g[i];
        }
        deg[node] += 1;
    }
    for (int i = 1; i <= deg[node]; ++i) {
        dp[node][i] = (ll)dp[node][i] * fact[i] % MOD;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 2; i <= n; ++i) {
        int u, v;
        std::cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    fact[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fact[i] = (ll)fact[i - 1] * i % MOD;
    }

    dfs(1, 0);
    int ans = 0;
    for (int i = 0; i <= deg[1]; ++i) {
        ans = (ans + dp[1][i]) % MOD;
    }
    std::cout << ans << '\n';

    return 0;
}