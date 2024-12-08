#include <bits/stdc++.h>

using ll = long long int;
const int MAXP = 100, MAXN = 2e5 + 19, MOD = 998244353;

constexpr int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = (ll)res * a % MOD;
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}

int n, p[MAXN];
int dp[MAXP], inv[MAXP + 1];

int main() {
    for (int i = 1; i <= MAXP; ++i) {
        inv[i] = qpow(i, MOD - 2);
    }

    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> p[i];
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < MAXP; ++j) {
            dp[j] = (ll)dp[j] * j % MOD * inv[100] % MOD;
        }
        // f[n] = 1 + p**1 * f[n] + p**2 * f[n - 1] + p**3 * f[n - 2]
        // f[n] = 1 + \sum_{i=1}^n p**(n-i+1) * f[i]
        // (1-p)f[n] = 1 + \sum_{i=1}^{n-1} p**(n-i+1) * f[i]
        int f = (1 + dp[p[i]]) * 100LL % MOD * inv[100 - p[i]] % MOD;
        ans = (ans + f) % MOD;
        for (int j = 0; j < MAXP; ++j) {
            dp[j] = (dp[j] + (ll)f * j % MOD * inv[100]) % MOD;
        }
    }

    std::cout << ans << '\n';
}