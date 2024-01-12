#include <bits/stdc++.h>

using ll = long long int;

constexpr int MAXN = 1e5 + 19;

int n, a[MAXN];

void solve(void) {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    int ans = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = l;
        if (a[l] != 0) {
            continue;
        }
        while (r + 1 <= n && a[r + 1] == 0) {
            ++r;
        }
        ans = std::max(ans, r - l + 1);
    }
    std::cout << ans << '\n';
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}