#include <iostream>
#include <vector>
#include <cstdint>
#include <numeric>

using ll = long long int;
const int MOD = 998244353;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = (ll)res * a % MOD;
        }
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}

int n;
std::vector<std::vector<int>> G;
std::vector<uint8_t> vist;
std::vector<int> dp, g, a;

int adder, multiplier;
void dfs(int node, int f) {
    for (int to : G[node]) {
        if (to == f) {
            continue;
        }
        dfs(to, node);
    }
    if (vist[node]) {
        dp[node] = a[node];
        g[node] = 1;
        for (int to : G[node]) {
            if (to == f || !vist[to]) {
                continue;
            }
            dp[node] = ((ll)dp[node] * g[to] + (ll)dp[to] * g[node] + (ll)dp[node] * dp[to]) % MOD;
            g[node] = ((ll)g[node] * g[to] + (ll)g[node] * dp[to]) % MOD;
        }
        if (f == -1 || !vist[f]) {
            adder -= 1;
            multiplier = (ll)multiplier * dp[node] % MOD;
        }
    }
}

int solve() {
    a.clear(), a.resize(n);
    for (int i = 0; i < n; ++i) {
        if (vist[i]) {
            for (int to : G[i]) {
                if (!vist[to]) {
                    a[i] += 1;
                }
            }
        }
    }
    int res = std::accumulate(a.begin(), a.end(), 0);

    adder = 0, multiplier = 1;
    dfs(0, -1);

    return (ll)qpow(2, res + adder) * multiplier % MOD;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    G.resize(n), vist.resize(n);
    dp.resize(n), g.resize(n);

    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        u -= 1, v -= 1;
        G[u].push_back(v), G[v].push_back(u);
    }

    for (int i = 1; i < n; ++i) {
        int x;
        std::cin >> x;
        vist[x - 1] = true;
        std::cout << solve() << '\n';
    }
}
