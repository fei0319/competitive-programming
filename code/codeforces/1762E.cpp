#include <bits/stdc++.h>

using ll = long long int;

const int MOD = 998244353, N = 1e6;

constexpr int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = (ll)res * a % MOD;
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}

int f(int n) {
    if (n <= 2) return 1;
    return qpow(n, n - 2);
}

int fact[N + 1], ifact[N + 1];
int binom(int n, int m) {
    return (ll)fact[n] * ifact[m] % MOD * ifact[n - m] % MOD;
}

int main() {
    fact[0] = 1;
    for (int i = 1; i <= N; ++i) fact[i] = (ll)fact[i - 1] * i % MOD;
    ifact[N] = qpow(fact[N], MOD - 2);
    for (int i = N - 1; i >= 0; --i)
        ifact[i] = (ll)ifact[i + 1] * (i + 1) % MOD;

    int n;
    std::cin >> n;

    if (n & 1) {
        std::cout << "0\n";
        return 0;
    }

    int ans = 0;
    for (int i = 1; i < n; ++i) {
        int t = (ll)f(i) * f(n - i) % MOD;
        t = (ll)t * i % MOD * (n - i) % MOD;
        t = (ll)t * binom(n, i) % MOD;
        t = (ll)t * i % MOD * (n - i) % MOD;
        if (i & 1) {
            ans = (ans - t) % MOD;
        } else {
            ans = (ans + t) % MOD;
        }
    }
    ans = (ll)ans * qpow((ll)n * (n - 1) % MOD, MOD - 2) % MOD;

    std::cout << (ans + MOD) % MOD << '\n';

    return 0;
}