#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 5e3 + 19;
const int MOD = 998244353;

constexpr int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = (ll)res * a % MOD;
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}

int n;
std::vector<int> f, g;

int fact[MAXN], ifact[MAXN];

void add(int &x, ll y) {
    x = (x + y) % MOD;
}

int main() {
    std::cin >> n;
    f.resize(n + 1);
    g.resize(n + 1);

    fact[0] = 1;
    for (int i = 1; i <= n; ++i) fact[i] = (ll)fact[i - 1] * i % MOD;
    ifact[n] = qpow(fact[n], MOD - 2);
    for (int i = n - 1; i >= 0; --i) {
        ifact[i] = (ll)ifact[i + 1] * (i + 1) % MOD;
    }
    std::copy(ifact, ifact + n + 1, f.begin());
    
    for (int i = 2; i <= n; ++i) {
        int v = f[i], p = 1;
        std::fill(g.begin(), g.end(), 0);
        for (int j = 0; i * j <= n; ++j) {
            int x = (ll)p * ifact[j] % MOD;
            for (int k = 0; k + i * j <= n; ++k) {
                add(g[k + i * j], (ll)f[k] * x);
            }

            p = (ll)p * v % MOD;
        }
        f.swap(g);
    }

    std::cout << ((ll)f[n] * fact[n] + MOD - 2) % MOD << '\n';

    return 0;
}