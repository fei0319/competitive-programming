#include <bits/stdc++.h>

using i64 = int64_t;
constexpr i64 INF = 1e18;

struct Node {
    std::vector<std::pair<i64, i64>> p;
    void insert(i64 l, i64 r) {
        p.emplace_back(l, r);
    }
    i64 get() {
        std::sort(p.begin(), p.end());

        i64 res = 0;
        i64 L = -INF, R = -INF - 1;
        for (auto [l, r] : p) {
            if (l > R) {
                res += R - L + 1;
                L = l;
            }
            R = std::max(R, r);
        }

        res += R - L + 1;
        return res;
    }
};

int main() {
    int n;
    i64 x, d;
    std::cin >> n >> x >> d;

    if (d == 0) {
        if (x == 0) {
            std::cout << "1\n";
        } else {
            std::cout << n + 1 << '\n';
        }

        return 0;
    }

    std::map<i64, Node> mt;

    if (d < 0) {
        x = x + (n - 1) * d;
        d = -d;
    }

    for (int i = 0; i <= n; ++i) {
        i64 min = i * (x + (x + (i - 1) * d)) / 2;
        i64 max = i * (x + (n - 1) * d + x + (n - i) * d) / 2;

        i64 reminder = (min % d + d) % d;
        mt[reminder].insert((min - reminder) / d, (max - reminder) / d);
    }

    i64 ans = 0;
    for (auto &[k, v] : mt) {
        ans += v.get();
    }

    std::cout << ans << '\n';

    return 0;
}