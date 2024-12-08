#include <bits/stdc++.h>

using ll = long long int;
using hash_t = uint64_t;

const int MAXN = 109, MOD = 998244353;

constexpr int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = (ll)res * a % MOD;
        }
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}

void add(auto &a, const auto &b) { a = (a + b) % MOD; }

int n, k;
std::vector<int> G[MAXN];

int size[MAXN];
std::vector<std::vector<int>> dp[MAXN], tmp;
// i subtree, take j, leave k to father

void dfs(int node, int f) {
    size[node] = 0;
    dp[node] = {{1}};

    for (int to : G[node]) {
        if (to == f) {
            continue;
        }
        dfs(to, node);

        tmp.resize(size[node] + size[to] + 1);
        for (int x = 0; x <= size[node] + size[to]; ++x) {
            tmp[x].clear();
            tmp[x].resize(size[node] + size[to] - x + 1);
        }

        for (int x = size[node]; x >= 0; --x) {
            for (int y = size[node] - x; y >= 0; --y) {
                for (int u = 0; u <= size[to]; ++u) {
                    for (int v = 0; u + v <= size[to]; ++v) {
                        add(tmp[x + u][y + v],
                            (ll)dp[node][x][y] * dp[to][u][v]);
                    }
                }
            }
        }
        dp[node].swap(tmp);

        size[node] += size[to];
    }

    size[node] += 1;
    tmp.resize(size[node] + 1);
    for (int x = 0; x <= size[node]; ++x) {
        tmp[x].clear();
        tmp[x].resize(size[node] - x + 1);
    }

    for (int x = size[node] - 1; x >= 0; --x) {
        for (int y = size[node] - 1 - x; y >= 0; --y) {
            add(tmp[x + 1][0], dp[node][x][y]);
            add(tmp[x][y + 1], dp[node][x][y]);
        }
    }
    dp[node].swap(tmp);
}

int fact[MAXN];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> k;
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

    int ans = 0;
    for (int rt = 1; rt <= n; ++rt) {
        dfs(rt, 0);
        for (int i = 0; i < n; ++i) {
            int res = 0;
            for (int j = k + 1; i + j <= n; ++j) {
                add(res, dp[rt][i][j]);
            }
            add(ans, (ll)res * fact[n - i - 1] % MOD * fact[i]);
        }
    }

    ans = (ll)ans * qpow(fact[n], MOD - 2) % MOD;
    std::cout << ans << '\n';

    return 0;
}