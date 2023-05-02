#include <bits/stdc++.h>

using ll = long long int;

ll calc(ll n) {
    ll l = 0, r = 1e9, res = 0;
    while (l < r) {
        ll mid = (l + r + 1) >> 1;
        if (mid * mid <= n) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    res += l;
    l = 0, r = 1e9;
    while (l < r) {
        ll mid = (l + r + 1) >> 1;
        if (mid * (mid + 1) <= n) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    res += l;
    l = 0, r = 1e9;
    while (l < r) {
        ll mid = (l + r + 1) >> 1;
        if (mid * (mid + 2) <= n) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    res += l;
    return res;
}

void solve(void) {
    ll l, r;
    std::cin >> l >> r;
    std::cout << calc(r) - calc(l - 1) << std::endl;
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