#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 103, INF = 1e9;

int n, a[MAXN];
int dp[MAXN][MAXN][2][2];

void update(int &x, int y) {
    if (y < x)
        x = y;
}

void solve() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }

    for (int l = 1; l <= n; ++l) {
        for (int r = l; r <= n; ++r) {
            dp[l][r][0][0] = INF;
            dp[l][r][0][1] = INF;
            dp[l][r][1][0] = INF;
            dp[l][r][1][1] = INF;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int r = std::min(i + a[i] - 1, n); r > i; --r) {
            dp[i][r][1][0] = 1;
        }
        for (int l = std::max(i - a[i] + 1, 1); l < i; ++l) {
            dp[l][i][0][1] = 1;
        }
        dp[i][i][1][1] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        int r = std::min(i + a[i] - 1, n);
        for (int j = i + 1; j < r; ++j) {
            int l = std::max(j - a[j] + 1, 1);
            if (l < i) {
                for (int u = l; u < i; ++u) {
                    for (int v = r; v > j; --v) {
                        dp[u][v][0][0] = 2;
                    }
                }
            }
        }
    }

    for (int l = n; l >= 1; --l) {
        for (int r = l; r <= n; ++r) {
            for (int b = 0; b < 4; ++b) {
                int x = b & 1, y = bool(b & 2);
                for (int m = l; m < r; ++m) {
                    int u = std::min(dp[l][m][x][0], dp[l][m][x][1]),
                        v = std::min(dp[m + 1][r][0][y], dp[m + 1][r][1][y]);
                    update(dp[l][r][x][y], u + v);
                }
                if (dp[l][r][x][y] != INF) {
                    int val = dp[l][r][x][y];
                    if (!x) {
                        for (int p = std::max(l - a[l] + 1, 1); p < l; ++p) {
                            update(dp[p][r][0][y], val + 1);
                        }
                    }
                    if (!y) {
                        for (int p = std::min(r + a[r] - 1, n); p > r; --p) {
                            update(dp[l][p][x][0], val + 1);
                        }
                    }
                }
            }
        }
    }

    int ans = std::min(
        {dp[1][n][0][0], dp[1][n][0][1], dp[1][n][1][0], dp[1][n][1][1]});
    std::cout << ans << '\n';
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