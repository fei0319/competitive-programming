#include <bits/stdc++.h>

void solve() {
    int h, w;
    std::cin >> h >> w;

    std::vector<int> a(h);
    for (int i = 0; i < h; ++i) {
        std::string str;
        std::cin >> str;
        for (int j = 0; j < w; ++j) {
            if (str[j] == '#') {
                a[i] |= 1 << j;
            }
        }
    }

    std::vector<int> dp(1 << w);
    for (int S = 0; S < (1 << w); ++S) {
        dp[S] = __builtin_popcount(S ^ a[0]);
    }

    auto check = [w](int S, int T) -> bool {
        for (int i = 0; i + 1 < w; ++i) {
            if (((S >> i) & 3) == 3 && ((T >> i) & 3) == 3) {
                return false;
            }
        }
        return true;
    };

    for (int i = 1; i < h; ++i) {
        std::vector<int> next_dp(1 << w);
        for (int S = 0; S < (1 << w); ++S) {
            int min = dp[0];
            for (int T = 0; T < (1 << w); ++T) {
                if (dp[T] < min && check(S, T)) {
                    min = dp[T];
                }
            }
            next_dp[S] = min + __builtin_popcount(S ^ a[i]);
        }
        dp = std::move(next_dp);
    }

    std::cout << std::ranges::min(dp) << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) solve();
}
