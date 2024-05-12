#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2.5e6 + 19, mod = 1e9 + 7;

int d, fact[maxn];

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

int get_highest(std::vector<int> f) {
    int d = f.size() - 1, res = 0;
    for (int i = 0; i <= d; ++i) {
        int tmp =
            (ll)fact[i] % mod * fact[d - i] % mod * ((d - i) % 2 ? -1 : 1);
        tmp = qpow(tmp, mod - 2);

        res = (res + (ll)tmp * f[i]) % mod;
    }
    return (res + mod) % mod;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> d;
    fact[0] = 1;
    for (int i = 1; i <= d; ++i) {
        fact[i] = (ll)fact[i - 1] * i % mod;
    }

    std::vector<int> f(d + 1), g(d + 1);
    for (int &i : f) {
        std::cin >> i;
    }
    for (int &i : g) {
        std::cin >> i;
    }

    int fd = get_highest(f), gd = get_highest(g);
    for (int i = 0; i <= d; ++i) {
        f[i] += mod - (ll)qpow(i, d) * fd % mod;
        g[i] += mod - (ll)qpow(i, d) * gd % mod;

        f[i] %= mod;
        g[i] %= mod;
    }
    f.pop_back(), g.pop_back();
    int fd1 = get_highest(f), gd1 = get_highest(g);

    std::cout << (ll(gd1 - fd1) * qpow((ll)d * fd % mod, mod - 2) % mod + mod) %
                     mod
              << '\n';

    return 0;
}