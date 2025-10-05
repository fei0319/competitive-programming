#include <bits/stdc++.h>

using fp = long double;
using i64 = int64_t;

void solve() {
    int n, k, x;
    std::cin >> n >> k >> x;

    std::vector<int> a(n);
    for (int &i : a) std::cin >> i;

    auto check = [&](fp v) -> bool {
        i64 c = 0;
        int g = 0;
        for (int i : a) {
            if (i >= v) {
                c += (1LL << (63 - __builtin_clzll(i / v)));
                g += 1;
            }
        }

        if (k <= c - g) return g + k >= x;
        return c - (k - (c - g)) >= x;
    };

    fp l = 0, r = std::ranges::max(a);
    while (r - l > 1e-10) {
        fp mid = (l + r) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }

    std::cout << l << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << std::fixed << std::setprecision(12);

    int t;
    std::cin >> t;

    while (t--) solve();
}
