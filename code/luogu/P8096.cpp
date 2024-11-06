#include <algorithm>
#include <cstdio>

const int maxn = 1e2 + 19, maxh = 1e3 + 19;
const int mod = 1e9 + 7;

int n, h[maxn], H[maxn], minh = 1e9;
int dp[maxn][maxh], ans;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", H + i), minh = std::min(minh, H[i]);
    dp[0][0] = 1;
    if (n % 2 == 0) minh = 0;
    for (int r = minh; r >= 0; --r) {
        for (int i = 1; i <= n; ++i) h[i] = H[i] - r;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= h[i - 1]; ++j)
                dp[i][j] = dp[i - 1][h[i - 1] - j];
            for (int j = h[i - 1] + 1; j <= h[i]; ++j) dp[i][j] = 0;
            for (int j = 1; j <= h[i]; ++j)
                dp[i][j] = (dp[i][j] + dp[i][j - 1]) % mod;
        }
        ans = (ans + dp[n][h[n]]) % mod;
    }
    printf("%d\n", ans);
}