#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

ll n, s, a[maxn], u[maxn], v[maxn];

void solve(void) {
    std::cin >> n >> s;
    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];
    std::pair<ll, ll> dp; // s, a - s
    for (int i = 2; i < n; ++i) {
        u[i] = s, v[i] = a[i] - s;
        if (a[i] < s)
            u[i] = 0, v[i] = a[i];
        dp = {
            std::min(dp.first + u[i - 1] * v[i], dp.second + v[i - 1] * v[i]),
            std::min(dp.first + u[i - 1] * u[i], dp.second + v[i - 1] * u[i])};
        if (i == 2) {
            dp = {a[1] * v[i], a[1] * u[i]};
        }
    }
    std::cout << std::min(dp.first + u[n - 1] * a[n],
                          dp.second + v[n - 1] * a[n])
              << '\n';
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