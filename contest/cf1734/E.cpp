#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e3 + 19;

int n, b[maxn];

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = (ll)res * a % n;
        }
        a = (ll)a * a % n, b >>= 1;
    }
    return res;
}

void solve(void) {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> b[i];
    }
    if (n == 2) {
        std::cout << b[1] << ' ' << b[1] << '\n';
        std::cout << 1 - b[2] << ' ' << b[2];
        return;
    }
    int r2 = qpow(2, n - 2);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) {
                std::cout << b[i] << ' ';
            } else {
                std::cout << ((i * (i - j) + (ll)(b[i] + b[j]) * r2) % n + n) %
                                 n
                          << ' ';
            }
        }
        std::cout << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    T = 1;

    while (T--) {
        solve();
    }

    return 0;
}