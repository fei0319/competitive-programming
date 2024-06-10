#include <bits/stdc++.h>

using i64 = int64_t;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }

    i64 l = 0, r = 0;
    for (int i = 1; i <= n; ++i) {
        i64 n_l, n_r;
        n_l = std::min({l + a[i], llabs(l + a[i]), llabs(r + a[i])});
        n_r = std::max({r + a[i], llabs(l + a[i]), llabs(r + a[i])});
        l = n_l;
        r = n_r;
    }

    std::cout << r << '\n';
}

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
}