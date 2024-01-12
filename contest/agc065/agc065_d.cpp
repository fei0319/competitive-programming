#include <bits/stdc++.h>

using ll = long long int;

const int MOD = 1e9 + 7;
const int N = 1e7, L = 3 * N;
int fact[L + 1], ifact[L + 1];

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1)
            res = (ll)res * a % MOD;
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}

int binom(int n, int m) {
    return (ll)fact[n] * ifact[n - m] % MOD * ifact[m] % MOD;
}

int main(int argc, char *argv[]) {
    fact[0] = 1;
    for (int i = 1; i <= L; ++i)
        fact[i] = (ll)fact[i - 1] * i % MOD;
    ifact[L] = qpow(fact[L], MOD - 2);
    for (int i = L - 1; i >= 0; --i)
        ifact[i] = (ll)ifact[i + 1] * (i + 1) % MOD;

    int n;
    ll m;

    std::cin >> n >> m;

    if (m == 0) {
        std::cout << "1\n";
        return 0;
    }
    if (n == 1 || m >= 2 * n) {
        std::cout << "0\n";
        return 0;
    }

    int ans = 0;
    ll sign = m & 1 ? 1 : -1;
    for (int i = 1; i <= m; ++i) {
        int g = (ll)binom(n + i - 2, n - 2) * binom(n + i - 1, n - 2) % MOD;
        ans = (ans + sign * g * ifact[i - 1] % MOD * ifact[m - i]) % MOD;
        sign *= -1;
    }

    ans = (ll)ans * fact[m - 1] % MOD * qpow(n - 1, MOD - 2) % MOD;
    ans = (ans + MOD) % MOD;

    std::cout << ans;

    return 0;
}