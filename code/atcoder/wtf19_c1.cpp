#include <bits/stdc++.h>

using i64 = int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::pair<i64, i64>> p(n);
    for (auto &[x, y] : p) {
        std::cin >> x >> y;
    }

    auto check = [&](i64 x, i64 y) -> bool {
        bool r{false};
        for (const auto &[a, b] : p) {
            i64 dx = x - a;
            i64 dy = b - y;
            if (dx <= dy && (dx & dy) == dx) {
                r = !r;
            }
        }
        return r;
    };

    i64 l = -1e18, r = 1e18;
    while (l < r) {
        i64 mid = (l + r) / 2;
        if (mid == r) {
            mid -= 1;
        }
        if (check(mid, -((1ULL << 60) - 1))) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    std::cout << l << '\n';
}
