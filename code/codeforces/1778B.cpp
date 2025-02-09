#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e5 + 19;

int n, m, d;
int p[maxn], a[maxn], pos[maxn];

void solve(void) {
    std::cin >> n >> m >> d;
    for (int i = 1; i <= n; ++i) std::cin >> p[i];
    for (int i = 1; i <= m; ++i) std::cin >> a[i];
    for (int i = 1; i <= n; ++i) pos[p[i]] = i;

    int ans = 1e9;
    for (int i = 1; i < m; ++i) {
        if (pos[a[i]] > pos[a[i + 1]]) ans = 0;
        else
            ans = std::min(ans, pos[a[i + 1]] - pos[a[i]]);

        if (pos[a[i + 1]] > pos[a[i]] + d) ans = 0;
        else if (d <= n - 2)
            ans = std::min(ans, pos[a[i]] + d - pos[a[i + 1]] + 1);
    }

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