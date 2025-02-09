#include <bits/stdc++.h>

constexpr int maxn = 1e5 + 19;

int n, m;
int s[maxn];

void solve() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) s[i] = 0;
    int left = 0, right = 0, middle = 0;
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        if (x > 0) {
            if (s[x] == 0) ++middle;
            s[x] = 1;
        } else if (x == -1)
            ++left;
        else
            ++right;
    }
    //    printf("%d %d %d\n", left, right, middle);
    int ans = std::min(std::max(left, right), (m - middle)) + middle;
    for (int i = 1; i <= m; ++i) {
        int x = s[i];
        s[i] += s[i - 1];
        if (!x) continue;
        int left_empty = i - 1 - s[i - 1],
            right_empty = (m - i) - (middle - s[i]);
        //  printf("%d %d\n", left_empty, right_empty);
        ans = std::max(ans, std::min(left_empty, left) +
                                std::min(right_empty, right) + middle);
    }
    printf("%d\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
}