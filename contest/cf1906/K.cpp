#include <bits/stdc++.h>

using ll = long long int;
const int MAXN = 1 << 17, MOD = 998244353;
constexpr int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = (ll)res * a % MOD;
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}

int n, a[MAXN];

void inplace_fwt(auto f, const int n) {
    if (n == 1) {
        return;
    }
    auto g = f + n / 2;
    inplace_fwt(f, n / 2);
    inplace_fwt(g, n / 2);
    for (int i = 0; i < n / 2; ++i) {
        int u = f[i], v = g[i];
        f[i] = (u + v) % MOD;
        g[i] = (u - v) % MOD;
    }
}

void inplace_ifwt(auto f, int n) {
    if (n == 1) {
        return;
    }
    auto g = f + n / 2;
    for (int i = 0; i < n / 2; ++i) {
        int u = f[i], v = g[i];
        f[i] = ll(u + v) * qpow(2, MOD - 2) % MOD;
        g[i] = ll(u - v) * qpow(2, MOD - 2) % MOD;
    }
    inplace_ifwt(f, n / 2);
    inplace_ifwt(g, n / 2);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;

    int V = 1;
    for (int i = 1; i <= n; ++i) {
        int t;
        std::cin >> t;
        a[t] += 1;
        while (V <= t) {
            V <<= 1;
        }
    }

    std::vector<int> f(V);
    f[0] = n;
    for (int i = 1; i < V; ++i) {
        f[i] = a[i] * 2;
    }

    inplace_fwt(f.begin(), f.size());
    for (int &i : f) {
        int x = ll(i + n) * qpow(4, MOD - 2) % MOD;
        i = qpow(3, x) * qpow(-1, n - x);
    }
    inplace_ifwt(f.begin(), f.size());

    std::cout << (f[0] + MOD) % MOD << '\n';

    return 0;
}