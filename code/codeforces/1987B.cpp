#include <bits/stdc++.h>

using i64 = int64_t;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int &i : a) {
        std::cin >> i;
    }

    int max = 0;
    int t = 0;
    i64 ans = 0;
    for (int i : a) {
        if (i < max) {
            t = std::max(t, max - i);
            ans += max - i;
        } else {
            max = i;
        }
    }

    std::cout << ans + t << '\n';
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