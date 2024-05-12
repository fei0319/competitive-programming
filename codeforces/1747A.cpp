#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e5 + 19;

int n, a[maxn];

void solve(void) {
    std::cin >> n;
    ll s = 0;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        s += a[i];
    }
    std::cout << (s > 0 ? s : -s) << std::endl;
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