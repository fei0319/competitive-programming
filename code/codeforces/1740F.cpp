#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e3 + 19, mod = 998244353;

int n, cnt[maxn], dp[2][maxn][maxn], sum[maxn], ans, lim[maxn];

void solve(void) {
    std::cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        std::cin >> x;
        ++cnt[x];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            lim[i] += std::min(cnt[j], i);
        }
    }

    dp[0 & 1][0][n] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            sum[j] = 0;
        }
        int prev = (i - 1) ? lim[i - 1] / (i - 1) : n;
        for (int v = lim[i] / i; v >= 1; --v) {
            while (prev >= v) {
                for (int s = prev * (i - 1); s <= lim[i]; ++s) {
                    sum[s] = (sum[s] + dp[i & 1 ^ 1][s][prev]) % mod;
                }
                --prev;
            }
            for (int s = v * i; s <= lim[i]; ++s) {
                dp[i & 1][s][v] = sum[s - v];
            }
        }
        for (int v = lim[i] / i; v >= 1; --v) {
            ans = (ans + dp[i & 1][n][v]) % mod;
        }
    }

    std::cout << ans << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    T = 1;

    while (T--) {
        solve();
    }

    return 0;
}