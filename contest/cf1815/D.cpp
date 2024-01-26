#include <bits/stdc++.h>

using ll = long long int;

const int MOD = 998244353;
const int B = 62;

void solve() {
    ll n;
    int m;
    std::cin >> n >> m;
    if (m >= 3) {
        int t = (n + 1) / 2 % MOD;
        int ans = (ll)t * t % MOD;
        if (n % 2 == 0) {
            ans = (ans + t) % MOD;
        }
        std::cout << ans << '\n';
        return;
    }
    if (m == 1) {
        std::cout << n % MOD << '\n';
        return;
    }

    auto calc = [&n](std::array<int, 2> f, int b) {
        for (int i = b - 1; i >= 0; --i) {
            auto g = f;
            if (n & (1LL << i)) {
                f[0] = g[0];
                f[1] = (g[0] + g[1]) % MOD;
            } else {
                f[0] = (g[0] + g[1]) % MOD;
                f[1] = g[1];
            }
        }
        return f[0];
    };

    int ans = 0;
    std::array<int, 2> f {1, 0};
    for (int i = B - 1; i >= 0; --i) {
        int c = 0;
        auto g = f;
        if (n & (1LL << i)) {
            f[0] = g[0];
            f[1] = (g[0] + g[1]) % MOD;
            c = (ll)g[0] * calc({1, 0}, i)% MOD;
        } else {
            f[0] = (g[0] + g[1]) % MOD;
            f[1] = g[1];
            c = (ll)g[1] * calc({0, 1}, i) % MOD;
        }
        ans = (ans + (1LL << i) % MOD * c) % MOD;
    }
    std::cout << ans << '\n';
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