#include <bits/stdc++.h>

using ll = long long int;

const int N = 2e3 + 19, M = 5e3;
const int MOD = 1e9 + 7;

constexpr int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1)
            res = (ll)res * a % MOD;
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}

int H[N + 1][N + 1];
int fact[M + 1], ifact[M + 1];
int binom(int n, int m) {
    return (ll)fact[n] * ifact[n - m] % MOD * ifact[m] % MOD;
}

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;

    if (n < k || m < k) {
        std::cout << "0\n";
        return;
    }
    int p = n + m - 2 * k + 1;
    int u = p / 2, v = p - u;

    int ans = 0;
    for (int i = 0; i <= k; ++i) {
        ans = (ans + (ll)H[u][i] * H[v][k - i]) % MOD;
    }
    ans = (ans + MOD) % MOD;

    std::cout << ans << '\n';
}

int main() {
    fact[0] = 1;
    for (int i = 1; i <= M; ++i)
        fact[i] = (ll)fact[i - 1] * i % MOD;
    ifact[M] = qpow(fact[M], MOD - 2);
    for (int i = M - 1; i >= 0; --i)
        ifact[i] = (ll)ifact[i + 1] * (i + 1) % MOD;

    H[0][0] = 1;
    for (int i = 0; i <= N; ++i) {
        H[1][i] = (ll)binom(2 * i, i) * qpow(i + 1, MOD - 2) % MOD;
    }
    for (int i = 2; i <= N; ++i) {
        for (int j = 0; j <= N - i; ++j) {
            H[i][j] = (H[i - 1][j + 1] - H[i - 2][j + 1]) % MOD;
        }
    }

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}