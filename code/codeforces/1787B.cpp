#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxp = 100;

void solve(void) {
    int n;
    std::cin >> n;
    static ll a[maxp];
    for (int i = 0; i < maxp; ++i) a[i] = 1;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            int p = 0;
            while (n % i == 0) {
                n /= i;
                a[++p] *= i;
            }
        }
    }
    a[1] *= n;
    ll ans = 0ll;
    for (int i = 0; i < maxp; ++i)
        if (a[i] != 1) {
            ans += a[i];
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