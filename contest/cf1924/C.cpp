#include <bits/stdc++.h>

using ll = long long int;
const int MOD = 999999893;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1)
            res = (ll)res * a % MOD;
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}

void solve() {
    int n;
    std::cin >> n;
    if (n == 1) {
        std::cout << "0\n";
        return;
    }
    if (n % 2 == 0) {
        int y = qpow(2, n / 2);
        int a = (4 - 4LL * y) % MOD;
        int b = (2LL * y * y - 8LL * y + 4) % MOD;
        std::cout << ((ll)a * qpow(b, MOD - 2) % MOD + MOD) % MOD;
    } else {
        int y = qpow(2, (n + 1) / 2);
        int a = (4 - 2LL * y) % MOD;
        int b = (-1LL * y * y - 4LL * y + 4) % MOD;
        std::cout << ((ll)a * qpow(b, MOD - 2) % MOD + MOD) % MOD;
    }
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}