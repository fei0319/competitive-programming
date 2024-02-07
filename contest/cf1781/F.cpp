#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 5e2 + 19, MOD = 998244353;

constexpr int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = (ll)res * a % MOD;
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}

int n, p;
int f[MAXN][MAXN], g[MAXN][MAXN];
int F[MAXN][MAXN], G[MAXN][MAXN];
int fact[MAXN], ifact[MAXN];

int main() {
    std::cin >> n >> p;
    p = (ll)p * qpow(10000, MOD - 2) % MOD;

    fact[0] = 1;
    for (int i = 1; i <= n; ++i) fact[i] = (ll)fact[i - 1] * i % MOD;
    ifact[n] = qpow(fact[n], MOD - 2);
    for (int i = n - 1; i >= 0; --i) ifact[i] = (ll)ifact[i + 1] * (i + 1) % MOD;

    for (int i = 0; i <= n; ++i) {
        F[i][0] = 1;
    }

    f[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        g[i][0] = (ll)p * (f[i - 1][0] + f[i - 1][1]) % MOD;
        for (int j = 1; j <= i; ++j) {
            g[i][j] = ((ll)p * f[i - 1][j + 1] + (ll)(1 - p) * f[i - 1][j - 1]) % MOD;
        }

        int s = 0;
        for (int j = 0; j <= n; ++j) {
            s = (s + g[i][j]) % MOD;
            G[j][i] = s;
            for (int k = 1; k <= i; ++k) {
                F[j][i] = (F[j][i] + (ll)F[j][i - k] * G[j][k] % MOD * ifact[k]) % MOD;
            }
        }

        f[i][0] = (ll)F[0][i] * fact[i] % MOD;
        for (int j = 1; j <= i; ++j) {
            f[i][j] = (ll)(F[j][i] - F[j - 1][i]) * fact[i] % MOD;
        }
    }

    int d = 1;
    for (int i = 1; i <= n; ++i) {
        d = (ll)d * (i * 2 - 1) % MOD;
    }
    int ans = (ll)f[n][0] * qpow(d, MOD -2) % MOD;
    std::cout << (ans + MOD) % MOD << '\n';

    return 0;
}