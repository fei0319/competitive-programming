#include <algorithm>
#include <cstdio>

using ll = long long int;

constexpr int MAXN = 2e5 + 19;

int n, a[MAXN], dp[MAXN], val[MAXN];

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        dp[i] = -1e9;
        val[i] = 0;
    }
    int ans = 0;
    dp[a[1]] = -1;
    for (int i = 2; i <= n; ++i) {
        int c = a[i];
        val[i] = std::max(val[i - 1], dp[c] + i + 1);
        ans = std::max(ans, val[i]);
        dp[c] = std::max(dp[c], val[i - 1] - i);
    }
    printf("%d\n", ans);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
}