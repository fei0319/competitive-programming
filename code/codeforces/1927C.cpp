#include <bits/stdc++.h>

using ll = long long int;

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<uint8_t> a(k), b(k);
    for (int i = 0; i < n; ++i) {
        int t;
        std::cin >> t;
        if (t <= k) a[t - 1] = true;
    }
    for (int i = 0; i < m; ++i) {
        int t;
        std::cin >> t;
        if (t <= k) b[t - 1] = true;
    }

    int x = k / 2, y = k / 2, p = 0;
    for (int i = 0; i < k; ++i) {
        if (a[i] && b[i]) {
            p += 1;
        } else if (a[i]) {
            x -= 1;
        } else if (b[i]) {
            y -= 1;
        } else {
            std::cout << "NO\n";
            return;
        }
    }
    //    std::cout << x << ' ' << y << '\n';

    if (x >= 0 && y >= 0) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
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