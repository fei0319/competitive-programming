#include <bits/stdc++.h>

using ll = long long int;

const int MOD = 998244353;

int qpow(int a, ll b) {
    int res = 1;
    while (b) {
        if (b & 1)
            res = (ll)res * a % MOD;
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}

void solve(void) {
    ll n;
    int p, k;

    std::cin >> n >> p >> k;

    int f = 1, g = 1;
    for (int r = 0; r <= k; ++r) {
        if (r > n) {
            std::cout << "0 ";
            continue;
        }

        if (r) {
            g = (ll)g * (qpow(p, r) - 1) % MOD;
        }

        int res = (ll)f * f % MOD *
                  qpow((ll)g * qpow(p, (ll)r * (r - 1) / 2) % MOD, MOD - 2) %
                  MOD;
        std::cout << (res + MOD) % MOD << ' ';

        f = (ll)f * (qpow(p, n) - qpow(p, r)) % MOD;
    }
}

int main(int argc, char *argv[]) {
    solve();

    return 0;
}