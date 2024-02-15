#include <bits/stdc++.h>

using ll = long long int;

const int MOD = 998244353;

void solve() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> G(n);
    for (int i = 2; i <= n; ++i) {
        int u, v;
        std::cin >> u >> v;
        G[u - 1].push_back(v - 1);
        G[v - 1].push_back(u - 1);
    }

    int ans = 0;
    std::vector<int> dp(n);
    std::function<void(int, int)> dfs = [&](int node, int f) {
        dp[node] = 1;
        for (int to : G[node]) {
            if (to == f) continue;
            dfs(to, node);
            dp[node] = (ll)dp[node] * (dp[to] + 1) % MOD;
            ans = (ans + dp[to]) % MOD;
        }
    };
    dfs(0, -1);
    ans = (ans + dp[0]) % MOD;
    ans = (ans + MOD + 1) % MOD;
    std::cout << ans << '\n';
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