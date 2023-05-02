#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e6 + 19;

int n, cnt[maxn];

void solve(void) {
    std::cin >> n;
    for (int i = 0; i <= n * 2; ++i)
        cnt[i] = 0;
    int s = 0;
    ++cnt[s];
    ll ans = (ll)n * (n + 1) / 2;
    for (int i = 1; i <= n; ++i) {
        int a;
        std::cin >> a;
        s ^= a;
        for (int j = 0; j * j <= n * 2; ++j)
            ans -= cnt[s ^ (j * j)];
        ++cnt[s];
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