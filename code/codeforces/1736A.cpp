#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e5 + 19;

int n, a[maxn], b[maxn];

void solve(void) {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        std::cin >> b[i];
    }
    int c[] = {0, 0};
    for (int i = 1; i <= n; ++i) {
        if (a[i] != b[i]) {
            ++c[a[i]];
        }
    }
    int ans = abs(c[0] - c[1]) + 1;
    if (c[0] + c[1] < ans) {
        ans = c[0] + c[1];
    }
    std::cout << ans << std::endl;
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