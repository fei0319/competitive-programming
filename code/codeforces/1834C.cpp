#include <algorithm>
#include <cstdio>

constexpr int MAXN = 1e5 + 19;

int n;
char s[MAXN], t[MAXN];

void solve() {
    scanf("%d", &n);
    scanf("%s%s", s + 1, t + 1);
    int cnt[] = {0, 0};
    for (int i = 1; i <= n; ++i) {
        if (s[i] != t[i])
            ++cnt[1];
        if (s[i] != t[n - i + 1])
            ++cnt[0];
    }
    int ans = 1e9;
    for (int i = 0; i < 2; ++i) {
        if (cnt[i])
            ans = std::min(ans, cnt[i] * 2 - (cnt[i] % 2 == i));
        else
            ans = std::min(ans, (1 - i) * 2);
    }

    printf("%d\n", ans);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--)
        solve();
}