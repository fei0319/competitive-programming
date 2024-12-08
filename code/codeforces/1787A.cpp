#include <bits/stdc++.h>

using ll = long long int;

void solve(void) {
    int n;
    std::cin >> n;
    ll ans = 0ll;
    if (n % 2 == 0) {
        std::cout << 1 << ' ' << n / 2 << '\n';
        return;
    }
    for (int x = 2; x <= 100; ++x)
        for (int y = 2; y <= 100; ++y) {
            ll xy = x * y, a = 1, b = 1;
            bool flag = false;
            for (int i = 1; i <= y - 1; ++i) {
                a *= x;
                if (a >= n) {
                    flag = true;
                    break;
                }
            }
            for (int i = 1; i <= x - 1; ++i) {
                b *= y;
                if (b >= n) {
                    flag = true;
                    break;
                }
            }
            if (flag) continue;
            if (xy * (a + b) == n) {
                std::cout << x << ' ' << y << '\n';
                return;
            }
        }
    std::cout << -1 << '\n';
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