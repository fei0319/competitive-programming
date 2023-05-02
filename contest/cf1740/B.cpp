#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

int n;
std::pair<int, int> a[maxn];
ll s[maxn];

void solve(void) {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i].first >> a[i].second;
        if (a[i].first < a[i].second) {
            std::swap(a[i].first, a[i].second);
        }
    }
    std::sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ++i) {
        s[i] = s[i - 1] + a[i].second;
    }
    int max_sec = 0;
    ll ans = 1e18, sum_fir = 0ll;
    for (int i = n; i >= 1; --i) {
        if (max_sec > a[i].first) {
            break;
        }
        ll res = (a[i].first + s[i] + sum_fir) << 1;
        ans = std::min(ans, res);
        sum_fir += a[i].first, max_sec = std::max(max_sec, a[i].second);
    }
    std::cout << ans << std::endl;
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