#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 3e6 + 19, N = 3e6, mod = 1e9 + 7;

int n, k;
int fact[maxn], ifact[maxn];

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = (ll)res * a % mod;
        a = (ll)a * a % mod, b >>= 1;
    }
    return res;
}

void init() {
    fact[0] = 1;
    for (int i = 1; i <= N; ++i) fact[i] = (ll)fact[i - 1] * i % mod;
    ifact[N] = qpow(fact[N], mod - 2);
    for (int i = N - 1; i >= 0; --i)
        ifact[i] = (ll)ifact[i + 1] * (i + 1) % mod;
}

int binom(int n, int m) {
    return (ll)fact[n] * ifact[n - m] % mod * ifact[m] % mod;
}

int empty_divide(int n, int m) { return binom(n + m - 1, m - 1); }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> k;
    if (k == 0) {
        std::cout << qpow(3, n) << std::endl;
        return 0;
    }
    init();

    int ans = 0;
    for (int i = 1; i <= k && i - 1 + k <= n; ++i) {
        int f = (ll)binom(k - 1, i - 1) * qpow(3, k - i) % mod, g = 0;
        //+-+
        g = (g +
             (ll)qpow(3, n - k - i + 1) * empty_divide(n - k - i + 1, i)) %
            mod;
        //+-+-
        if (n - k - i >= 0)
            g = (g +
                 (ll)qpow(3, n - k - i) * empty_divide(n - k - i, i + 1)) %
                mod;

        ans = (ans + (ll)f * g) % mod;
    }

    std::cout << ans << std::endl;

    return 0;
}