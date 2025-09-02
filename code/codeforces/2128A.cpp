#include <bits/stdc++.h>

using i64 = int64_t;

void solve() {
    int n;
    std::cin >> n;

    int c;
    std::cin >> c;

    std::vector<i64> a(n);
    for (i64 &i : a) {
        std::cin >> i;
    }

    int ans = 0;
    for (int _ = 0; _ < n; ++_) {
        int idx = 0;
        for (int i = 1; i < a.size(); ++i) {
            if (a[idx] > c || (a[i] <= c && a[i] > a[idx])) {
                idx = i;
            }
        }

        if (a[idx] > c) {
            ++ans;
        }
        a.erase(a.begin() + idx);
        std::for_each(a.begin(), a.end(), [](i64 &x) { x *= 2; });
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
