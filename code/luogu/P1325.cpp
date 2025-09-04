#include <bits/stdc++.h>

using real = double;

int main() {
    int n, d;
    std::cin >> n >> d;

    auto cover = [d](int x, int y) -> std::pair<real, real> {
        const double t =
            std::sqrt(static_cast<real>(d) * d - static_cast<real>(y) * y);
        return std::make_pair(x - t, x + t);
    };

    std::vector<std::pair<real, real>> a{};
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        if (y > d) {
            std::cout << "-1\n";
            return 0;
        }
        a.push_back(cover(x, y));
    }

    {
        std::vector<std::pair<real, real>> tmp{};
        std::swap(a, tmp);
        std::ranges::sort(tmp, [](const auto &p1, const auto &p2) {
            const auto [l1, r1] = p1;
            const auto [l2, r2] = p2;
            if (l1 != l2) return l1 < l2;
            return r1 > r2;
        });
        const auto ret = std::ranges::unique(tmp);
        tmp.erase(ret.begin(), ret.end());
        for (const auto [l, r] : tmp) {
            while (!a.empty() && a.back().second >= r) a.pop_back();
            a.emplace_back(l, r);
        }
    }

    std::vector<int> dp(a.size());
    for (int i = 0, l = 0; i < a.size(); ++i) {
        while (a[i].first > a[l].second) ++l;
        dp[i] = (l ? dp[l - 1] : 0) + 1;
    }

    std::cout << dp.back() << '\n';
}
