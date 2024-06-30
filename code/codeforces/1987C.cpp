#include <bits/stdc++.h>

using i64 = int64_t;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int &i : a) {
        std::cin >> i;
    }

    int ans = 0;
    for (int i = n - 1; i >= 0; --i) {
        ans = std::max(a[i], ans + 1);
    }

    std::cout << ans << '\n';
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