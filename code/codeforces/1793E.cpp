#include <bits/stdc++.h>

constexpr int INF = 1e9;

struct BIT {
    std::vector<int> tr;
    explicit BIT(int n) : tr(n + 1, -INF) {}
    int query(int x) {
        int res = 0;
        for (; x; x -= x & -x) {
            res = std::max(res, tr[x]);
        }
        return res;
    }
    void update(int x, int k) {
        for (; x < tr.size(); x += x & -x) {
            tr[x] = std::max(tr[x], k);
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }

    std::sort(std::next(a.begin()), a.end());
    auto mt = BIT{n};

    std::vector<int> dp(n + 1);
    for (int i = 1; i <= n; ++i) {
        dp[i] = -INF;
        if (i - a[i] >= 0) {
            dp[i] = std::max(mt.query(i - a[i]), 0) + 1;
        }
        mt.update(i, dp[i]);
    }

    std::vector<int> ans(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (dp[i] + n - i >= 0) {
            ans[dp[i] + n - i] = i;
        }
        ans[n - std::max(a[i], i) + 1] = i;
    }
    for (int i = n - 1; i >= 0; --i) {
        ans[i] = std::max(ans[i], ans[i + 1]);
    }

    int q;
    std::cin >> q;

    while (q--) {
        int k;
        std::cin >> k;
        std::cout << ans[k] << '\n';
    }

    return 0;
}