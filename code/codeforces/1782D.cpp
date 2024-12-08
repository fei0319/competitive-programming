#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e5 + 19;

int n, a[maxn];

inline bool is_square(ll x) {
    ll r = std::sqrt(x);
    return r * r == x || (r + 1) * (r + 1) == x || (r - 1) * (r - 1) == x;
}

int calc(ll x) {
    int res = 0;
    for (int i = 1; i <= n; ++i)
        if (is_square(a[i] + x)) ++res;
    return res;
}

void solve(void) {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    std::sort(a + 1, a + 1 + n);

    int ans = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j) {
            int d = a[j] - a[i];
            for (int x = 1; x * x < d; ++x)
                if (d % x == 0) {
                    int y = d / x;
                    if ((y - x) % 2 == 1) continue;
                    ll to = ll((y - x) / 2) * ((y - x) / 2);
                    if (to < a[i]) continue;
                    ans = std::max(ans, calc(to - a[i]));
                }
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