#include <bits/stdc++.h>

using ll = long long int;
constexpr int maxn = 1e7 + 19, mod = 1e9 + 7;

int n, m, f[maxn], p2[maxn], fact[maxn], ifact[maxn];
int binom(int n, int m) {
    return (ll)fact[n] * ifact[n - m] % mod * ifact[m] % mod;
}
int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = (ll)res * a % mod;
        }
        a = (ll)a * a % mod, b >>= 1;
    }
    return res;
}

void solve(void) {
    std::cin >> n >> m;
    if (m > n) {
        std::swap(n, m);
    }
    int ans = 0;
    for (int i = 0; i <= m; ++i) {
        ans = (ans + (ll)binom(n, i) * binom(m, i) % mod *
                         (f[n + m - i] + (ll)i * p2[n + m - i - 1] % mod)) %
              mod;
    }
    std::cout << ans << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    f[1] = qpow(2, mod - 2), fact[0] = 1, p2[0] = 1;
    for (int i = 2; i < maxn; ++i) {
        f[i] = f[i - 1] * 2 % mod;
    }
    for (int i = 1; i < maxn; ++i) {
        f[i] = (ll)f[i] * (i + 3) % mod;
        fact[i] = (ll)fact[i - 1] * i % mod;
        p2[i] = p2[i - 1] * 2 % mod;
    }
    ifact[maxn - 1] = qpow(fact[maxn - 1], mod - 2);
    for (int i = maxn - 2; i >= 0; --i) {
        ifact[i] = (ll)ifact[i + 1] * (i + 1) % mod;
    }

    while (T--) {
        solve();
    }

    return 0;
}