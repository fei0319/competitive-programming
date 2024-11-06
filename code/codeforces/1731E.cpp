#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e6 + 19;

int n;
ll m;
ll f[maxn];

void solve(void) {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) f[i] = ll(n / i) * (n / i - 1) / 2;
    for (int i = n; i >= 1; --i)
        for (int j = i + i; j <= n; j += i) f[i] -= f[j];
    //	for(int i = 1; i <= n; ++i){
    //		std::cout << "f_" << i << "=" << f[i] << '\n';
    //	}
    ll ans = 0;
    for (int i = n - 1; i >= 1; --i) {
        ll x = std::min(f[i + 1] / i, m / i);
        m -= x * i, ans += x * (i + 1);
    }
    if (m != 0ll) ans = -1;
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