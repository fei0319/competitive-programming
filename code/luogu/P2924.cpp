#include <algorithm>
#include <cmath>
#include <iostream>
#include <ranges>
#include <vector>

void solve() {
    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> a(n);
    for (auto &[x, y] : a) std::cin >> x >> y;

    std::vector<std::pair<int, int>> edge_list{};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            edge_list.emplace_back(i, j);
        }
    }
    std::ranges::sort(edge_list, [&](auto e1, auto e2) -> bool {
        auto get_vec = [&](auto e) {
            const auto [id1, id2] = e;
            const auto [x1, y1] = a[id1];
            const auto [x2, y2] = a[id2];
            return std::make_pair(x2 - x1, y2 - y1);
        };
        const auto [x1, y1] = get_vec(e1);
        const auto [x2, y2] = get_vec(e2);
        return std::atan2(y1, x1) < std::atan2(y2, x2);
    });

    auto work = [&](int s) -> int {
        std::vector<int> dp(n, std::numeric_limits<int>::min());
        dp[s] = 0;
        int res{};
        for (const auto [id1, id2] : edge_list) {
            if (id2 == s) res = std::max(res, dp[id1] + 1);
            else dp[id2] = std::max(dp[id2], dp[id1] + 1);
        }
        return res;
    };
    const int ans = std::ranges::max(std::views::iota(0, n) |
                                     std::views::transform(work));
    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();
}