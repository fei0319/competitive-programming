#include <bits/stdc++.h>

using ll = long long int;

void solve() {
    int n, m, k;
    std::vector<int> a;
    std::cin >> n >> m >> k;

    a.resize(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end());

    ll ans = 0;
    for (int i = 0; i < n && k; ++i) {
        int v = std::min(k, m);
        ans += (ll)a[i] * v;
        ans += (ll)(k - v) * v;
        k -= v;
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