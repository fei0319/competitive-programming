#pragma GCC optimize(2)

#include <cmath>
#include <cstdio>

constexpr int MAXN = 1.5e3 + 19, MOD = 1e9 + 7;

int n, k, a[MAXN];
int pos[MAXN], cnt;
int dp[2][MAXN][MAXN];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        if (a[i])
            pos[++cnt] = i;
    }

    for (int i = 0; i <= n; ++i)
        dp[0][i][0] = 1;
    for (int _ = 1; _ <= cnt; ++_) {
        for (int i = _ - 1; i <= n; ++i)
            for (int j = 0; j <= k; ++j)
                dp[_ & 1][i][j] = 0;
        for (int i = _; i <= n; ++i) {
            int cost = abs(pos[_] - i);
            for (int j = k; j >= cost; --j) {
                dp[_ & 1][i][j] =
                    (dp[_ & 1][i - 1][j] + dp[_ & 1 ^ 1][i - 1][j - cost]) %
                    MOD;
            }
            for (int j = cost - 1; j >= 0; --j) {
                dp[_ & 1][i][j] = dp[_ & 1][i - 1][j];
            }
        }
    }

    int ans = 0;
    for (int i = k; i >= 0; i -= 2)
        ans = (ans + dp[cnt & 1][n][i]) % MOD;
    printf("%d\n", ans);
}