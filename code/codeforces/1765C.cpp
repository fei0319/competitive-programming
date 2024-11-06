#include <bits/stdc++.h>

using ll = long long int;

const int N = 1e6;
const int MAXN = 501, MOD = 998244353;

constexpr int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = (ll)res * a % MOD;
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}

int n, k;
int f[MAXN * 4], tot[MAXN * 4];
int fact[N + 1], ifact[N + 1], inv[N + 1];

void add(int &a, int b) { a = (a + b) % MOD; }

int binom(int n, int m) {
    return (ll)fact[n] * ifact[n - m] % MOD * ifact[m] % MOD;
}

int dp[MAXN][MAXN * 4];

int main() {
    fact[0] = 1;
    for (int i = 1; i <= N; ++i) fact[i] = (ll)fact[i - 1] * i % MOD;
    ifact[N] = qpow(fact[N], MOD - 2);
    for (int i = N - 1; i >= 0; --i)
        ifact[i] = (ll)ifact[i + 1] * (i + 1) % MOD;
    for (int i = 1; i <= N; ++i) inv[i] = (ll)ifact[i] * fact[i - 1] % MOD;

    std::cin >> n >> k;

    for (int L = 1; L <= n; ++L) {
        dp[L][0] = 1;
        for (int t = 0; t < 3; ++t) {
            for (int i = n * 4; i >= 0; --i) {
                dp[L][i] = 0;
                for (int j = L; j <= n && j <= i; ++j) {
                    add(dp[L][i], (ll)dp[L][i - j] * binom(n, j) % MOD);
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        int t_i = (ll)qpow(binom(n, i), 1) * binom(4, 1) % MOD;

        for (int j = (i + 1) * 3; i + j <= n * 4; ++j) {
            int t = (ll)t_i * dp[i + 1][j] % MOD;
            int p = (ll)(n - i) * inv[n * 4 - i - j] % MOD;
            add(f[i + j], (ll)p * t % MOD);
            add(tot[i + j], t);
        }
    }

    for (int i = 0; i <= n; ++i) {
        int t_i = (ll)qpow(binom(n, i), 2) * binom(4, 2) % MOD;
        for (int a = i + 1; a <= n; ++a) {
            int t_a = (ll)t_i * binom(n, a) % MOD;
            for (int b = i + 1; b <= n; ++b) {
                int t_b = (ll)t_a * binom(n, b) % MOD;
                int p = (ll)(n - i) * inv[n * 4 - i - i - a - b] % MOD;
                add(f[i + i + a + b], (ll)p * t_b % MOD);
                add(tot[i + i + a + b], t_b);
            }
        }
    }
    for (int i = 0; i <= n; ++i) {
        int t_i = (ll)qpow(binom(n, i), 3) * binom(4, 3) % MOD;
        for (int a = i + 1; a <= n; ++a) {
            int t_a = (ll)t_i * binom(n, a) % MOD;
            int p = (ll)(n - i) * inv[n * 4 - i - i - i - a] % MOD;
            add(f[i + i + i + a], (ll)p * t_a % MOD);
            add(tot[i + i + i + a], t_a);
        }
    }
    for (int i = 0; i <= n; ++i) {
        int t_i = (ll)qpow(binom(n, i), 4) * binom(4, 4) % MOD;
        int p = (ll)(n - i) * inv[n * 4 - i - i - i - i] % MOD;
        add(f[i + i + i + i], (ll)p * t_i % MOD);
        add(tot[i + i + i + i], t_i);
    }

    int ans = 0;
    for (int i = 1; i <= n * 4; ++i) {
        int t = std::min(i - 1, k);
        ans = (ans + (ll)f[t] * qpow(tot[t], MOD - 2)) % MOD;
    }

    std::cout << ans << '\n';

    return 0;
}