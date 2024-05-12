#include <bits/stdc++.h>

using ll = long long int;

void solve() {
    int n, k;
    std::cin >> n >> k;

    int ans;
    if (k <= 4 * n - 4) {
        ans = (k + 1) / 2;
    } else {
        ans = k - (4 * n - 4) + (2 * n - 2);
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