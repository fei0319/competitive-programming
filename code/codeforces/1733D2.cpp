#include <bits/stdc++.h>

constexpr int maxn = 5e3 + 9;
using ll = long long int;

char s[maxn], t[maxn];
ll dp[maxn][maxn];

void solve(void) {
    int n, x, y;
    std::cin >> n >> x >> y;

    std::vector<int> pos;
    std::cin >> s + 1 >> t + 1;
    for (int i = 1; i <= n; ++i) {
        if (s[i] != t[i]) {
            pos.push_back(i);
        }
    }

    if (pos.size() % 2 == 1) {
        std::cout << -1 << std::endl;
        return;
    }

    if (x >= y) {
        if (pos.size() == 2ll && pos[0] == pos[1] - 1) {
            if ((pos[0] - 2 >= 1 || pos[1] + 2 <= n) && (ll)y * 2 <= x)
                std::cout << (ll)y * 2 << std::endl;
            else if ((pos[0] - 1 >= 1 && pos[1] + 1 <= n) &&
                     (ll)y * 3 <= x)
                std::cout << (ll)y * 3 << std::endl;
            else
                std::cout << x << std::endl;
        } else {
            std::cout << (ll)pos.size() / 2 * y << std::endl;
        }
        return;
    }

    int m = pos.size();
    dp[1][0] = 1e18, dp[1][1] = 0;
    if (m >= 2) {
        dp[2][0] = std::min((ll)x * (pos[1] - pos[0]), (ll)y),
        dp[2][1] = 1e18, dp[2][2] = 0;
    }
    for (int i = 3; i <= m; ++i) {
        for (int j = 0; j <= i; ++j) {
            dp[i][j] = 1e18;
        }
        for (int j = 0; j < i; ++j) {
            dp[i][j] = dp[i - 2][j] + (ll)x * (pos[i - 1] - pos[i - 2]);
        }
        for (int j = 0; j < i - 1; ++j) {
            dp[i][j] = std::min(dp[i][j], dp[i - 1][j + 1] + y);
        }
        for (int j = 1; j <= i; ++j) {
            dp[i][j] = std::min(dp[i][j], dp[i - 1][j - 1]);
        }
    }

    std::cout << dp[m][0] << std::endl;
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