#include <bits/stdc++.h>

std::mt19937 rng(std::random_device{}());

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> tail(n * 2 + 1);
    for (int i = 1; i <= n; ++i) {
        int u, v;
        std::cin >> u >> v;
        tail[u] = v;
    }

    std::vector<std::vector<std::pair<int, int>>> dp(n * 2 + 2);
    auto get = [&](int l, int r) -> int {
        auto it = std::upper_bound(dp[l].begin(), dp[l].end(),
                                   std::make_pair(r, static_cast<int>(1e9)));
        if (it == dp[l].begin()) {
            return 0;
        }
        return (--it)->second;
    };

    auto merge = [&](const std::vector<std::pair<int, int>> &a,
                     const std::vector<std::pair<int, int>> &b)
        -> std::vector<std::pair<int, int>> {
        int pa = 0, pb = 0;

        std::vector<std::pair<int, int>> res;
        auto insert = [&](const std::pair<int, int> &p) {
            auto [pos, val] = p;
            while (!res.empty() && res.back().first >= pos) {
                res.pop_back();
            }
            if (res.empty() || val > res.back().second) {
                res.emplace_back(pos, val);
            }
        };

        while (pa < a.size() && pb < b.size()) {
            if (a[pa].second < b[pb].second) {
                insert(a[pa++]);
            } else {
                insert(b[pb++]);
            }
        }
        while (pa < a.size()) {
            insert(a[pa++]);
        }
        while (pb < b.size()) {
            insert(b[pb++]);
        }

        return res;
    };

    for (int l = n * 2; l >= 1; --l) {
        dp[l] = dp[l + 1];
        if (tail[l]) {
            int r = tail[l];
            int v = 1;
            if (l + 1 < r - 1) {
                v += get(l + 1, r - 1);
            }

            std::vector<std::pair<int, int>> other;
            other.emplace_back(r, v);
            for (auto [pos, val] : dp[r + 1]) {
                other.emplace_back(pos, val + v);
            }

            dp[l] = merge(dp[l], other);
        }
    }

    std::cout << get(1, n * 2) << '\n';
}
