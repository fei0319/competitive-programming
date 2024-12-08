#include <bits/stdc++.h>

using ll = long long int;

void solve(void) {
    ll n, x;
    std::cin >> n >> x;
    ll l = n, r = 9e18, raw = n;
    for (int i = 0; i < 62; ++i) {
        //	std::cout << i << ":\n";
        if (x & (1ll << i)) {
            if (!(n & (1ll << i))) {
                std::cout << "-1\n";
                return;
            }
            r = std::min(r, raw + (1ll << i));
        } else if (n & (1ll << i)) {
            l = std::max(l, raw + (1ll << i));
            //		std::cout << (raw + (1ll << i)) << '\n';
        }
        //	std::cout << l << ' ' << r << '\n';
        if (raw & (1ll << i)) raw -= 1ll << i;
    }
    if (r <= l) {
        std::cout << "-1\n";
    } else {
        std::cout << l << '\n';
    }
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