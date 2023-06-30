#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

constexpr int MAXN = 3e5 + 19, MAXM = 11;

char s[MAXN], l[MAXM], r[MAXM];
int m, n, pos[256];

bool dp[MAXM][MAXN];

void solve() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    scanf("%d%s%s", &m, l + 1, r + 1);

    for (int i = 0; i <= m; ++i)
        for (int j = 0; j <= n; ++j)
            dp[i][j] = false;

    dp[0][0] = true;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 256; ++j)
            pos[j] = 0;
        for (int j = n; j >= 0; --j) {
            if (dp[i][j]) {
                for (int x = l[i + 1]; x <= r[i + 1]; ++x)
                    if (pos[x])
                        dp[i + 1][pos[x]] = true;
                    else {
                        puts("YES");
                        return;
                    }
            }
            if (j != 0)
                pos[s[j]] = j;
        }
    }
    puts(dp[m][0] ? "YES" : "NO");
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
}