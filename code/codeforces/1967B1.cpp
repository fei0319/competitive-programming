#include <bits/stdc++.h>

using ll = long long int;

void solve() {
    int n, m;
    std::cin >> n >> m;

    ll ans = 0;
    for (int i = 1; i <= m; ++i) {
        ans += (n / i + 1) / i;
    }
    ans -= 1;
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