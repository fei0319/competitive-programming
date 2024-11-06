#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e5 + 19;

int n, a[maxn];

void solve(void) {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];

    int tot = 0, dlt = -10;
    for (int i = 1; i <= n; ++i) {
        tot += a[i];
        if (i < n) dlt = std::max(dlt, -2 * (a[i] + a[i + 1]));
    }
    std::cout << tot + dlt << '\n';
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