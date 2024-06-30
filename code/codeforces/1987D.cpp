#include <bits/stdc++.h>

using i64 = int64_t;
constexpr i64 INF = 1e18;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int &i : a) {
        std::cin >> i;
    }
    std::sort(a.begin(), a.end());

    std::vector<i64> dp(n + 1, INF);
    dp[0] = 0;

    for (int l = 0, r; l < n; l = r + 1) {
        r = l;
        while (r + 1 < n && a[r + 1] == a[r]) {
            ++r;
        }
        int num = r - l + 1;

        std::vector<i64> ndp(n + 1, INF);
        for (int i = 1; i <= n; ++i) {
            ndp[i] = dp[i - 1] + 1;
        }
        for (int i = num; i <= n; ++i) {
            ndp[i - num] = std::min(ndp[i - num], dp[i]);
        }

        dp.swap(ndp);

        // for (auto i : dp) {
        //     std::cerr << i << " ";
        // }
        // std::cerr << "\n";
    }

    std::cout << *std::min_element(dp.begin(), dp.end()) << '\n';
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