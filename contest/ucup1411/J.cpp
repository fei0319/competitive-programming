#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, W;
    std::cin >> n >> W;

    const int B = 13, INF = 1e9;
    std::vector<int> a(B);

    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        a[x - 1] += 1;
    }

    std::vector<int> dp(1 << B, INF);
    std::vector<int> tot(1 << B);
    for (int i = 0; i < (1 << B); ++i) {
        for (int j = 0; j < B; ++j) {
            if (i & (1 << j)) {
                tot[i] += a[j];
            }
        }
    }

    dp[0] = 0;
    for (int i = 1; i < (1 << B); ++i) {
        for (int j = i & (i - 1);; j = (j - 1) & i) {
            if (tot[i ^ j] <= W) {
                dp[i] = std::min(dp[i], dp[j] + 1);
            }
            if (j == 0) {
                break;
            }
        }
    }
    std::cout << dp[(1 << B) - 1] << '\n';
}