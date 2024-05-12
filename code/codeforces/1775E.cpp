#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

int n, a[maxn];

void solve(void) {
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    ll pos = 0, neg = 0, ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i] > 0) {
            int x = std::min((ll)a[i], neg);
            neg -= x, pos += x;
            if (a[i] > x) {
                pos += a[i] - x;
                ans += a[i] - x;
            }
        } else {
            a[i] = -a[i];
            int x = std::min((ll)a[i], pos);
            pos -= x, neg += x;
            if (a[i] > x) {
                neg += a[i] - x;
                ans += a[i] - x;
            }
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