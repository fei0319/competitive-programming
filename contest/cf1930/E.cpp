#include <bits/stdc++.h>

using ll = long long int;

const int N = 5e6 + 19;
const int MOD = 998244353;

constexpr int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = (ll)res * a % MOD;
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}

int fact[N + 1], ifact[N + 1];
int binom(int n, int m) {
    return (ll)fact[n] * ifact[n - m] % MOD * ifact[m] % MOD;
}

void solve() {
    int n;
    std::cin >> n;
    for (int k = 1; k * 2 + 1 <= n; ++k) {
        int res = 0;
        for (int T = k * 2; T <= n; T += k * 2) {
            res = (res + binom(n, T)) % MOD;
            res = (res - binom(n - T + k * 2 - 1, k * 2 - 1)) % MOD;
        }
        res = (res + 1 + MOD) % MOD;
        std::cout << res << ' ';
    }
    std::cout << '\n';
}

int main() {
    fact[0] = 1;
    for (int i = 1; i <= N; ++i) {
        fact[i] = (ll)fact[i - 1] * i % MOD;
    }
    ifact[N] = qpow(fact[N], MOD - 2);
    for (int i = N - 1; i >= 0; --i) {
        ifact[i] = (ll)ifact[i + 1] * (i + 1) % MOD;
    }

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}