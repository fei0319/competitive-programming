#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 5e3 + 19, MOD = 1e9 + 7;

constexpr int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = (ll)res * a % MOD;
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}

int n, m, v, dp[MAXN][MAXN];
int a[MAXN];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m >> v;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        a[i] = (ll)a[i] * qpow(v, MOD - 2) % MOD;
    }

    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = (ll)dp[i - 1][0] * a[i] % MOD;
        for (int j = 1; j <= i; ++j) {
            dp[i][j] = (
                    (ll)dp[i - 1][j - 1] * (m - j + 1) % MOD * i +
                    (ll)dp[i - 1][j] * a[i] +
                    (ll)dp[i - 1][j] * j
                    ) % MOD;
        }
    }

    int ans = 0;
    for (int i = 0; i <= std::min(n, m); ++i) {
        ans = (ans + (ll)dp[n][i] * qpow(n, m - i)) % MOD;
    }
    ans = (ll)ans * qpow(v, n) % MOD;
    ans = (ll)ans * qpow(qpow(n, m), MOD - 2) % MOD;
    std::cout << ans << '\n';

    return 0;
}