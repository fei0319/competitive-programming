#include <bits/stdc++.h>

using ll = long long int;

int n, m;
std::vector<std::vector<int>> a, dp;

bool check(int x) {
    //	std::cout << "checking" << x << std::endl;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i][j] >= x)
                dp[i][j] = std::min(dp[i - 1][j], dp[i][j - 1]);
            else
                dp[i][j] = 0;
            if (a[i - dp[i][j]][j - dp[i][j]] >= x) ++dp[i][j];
            if (dp[i][j] >= x) return true;
            //			std::cout << dp[i][j] << ' ';
        }
        //		std::cout << std::endl;
    }
    return false;
}

void solve(void) {
    std::cin >> n >> m;
    a.resize(n + 1), dp.resize(n + 1);
    a[0].resize(m + 1), dp[0].resize(m + 1);
    for (int i = 1; i <= n; ++i) {
        a[i].resize(m + 1), dp[i].resize(m + 1);
        for (int j = 1; j <= m; ++j) std::cin >> a[i][j];
    }
    int l = 1, r = std::min(n, m);
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (check(mid)) l = mid;
        else
            r = mid - 1;
    }
    std::cout << l << '\n';
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