#include <bits/stdc++.h>

using i64 = int64_t;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> b(n);
    for (int &i : b) {
        std::cin >> i;
    }

    int min = b[0];
    for (int i = 1; i < n; ++i) {
        if (b[i] >= min * 2) {
            std::cout << "NO\n";
            return;
        }
        min = std::min(min, b[i]);
    }

    std::cout << "YES\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
}
