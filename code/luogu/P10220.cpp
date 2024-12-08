#ifdef ONLINE_JUDGE
#include <bits/stdc++.h>
#else
#include <algorithm>
#include <iostream>
#include <vector>
#endif

using i64 = int64_t;

constexpr i64 INF = 1e18;

void solve() {
    int n;
    i64 K;
    std::cin >> n >> K;

    std::vector<i64> w(1 << (n + 1));
    std::vector<int> q(1 << (n + 1));

    for (int i = 1; i < (1 << n); ++i) {
        std::cin >> w[i];
    }
    for (int i = (1 << n); i < (1 << (n + 1)); ++i) {
        std::cin >> q[i];
    }

    auto is_leaf = [&](int node) -> bool { return node >= (1 << n); };

    std::vector<i64> dp(1 << (n + 1));
    auto get_sentinel = [&](int node, i64 k) -> int {
        std::vector<int> leaves;
        auto dfs0 = [&](auto self, int node) -> void {
            if (is_leaf(node)) {
                leaves.push_back(node);
                return;
            }
            self(self, node << 1);
            self(self, node << 1 | 1);
        };
        dfs0(dfs0, node);

        auto check = [&](int val) -> bool {
            auto dfs1 = [&](auto self, int node) -> void {
                if (is_leaf(node)) {
                    if (q[node] < val) {
                        dp[node] = INF;
                    } else {
                        dp[node] = 0;
                    }
                    return;
                }
                self(self, node << 1);
                self(self, node << 1 | 1);
                dp[node] =
                    dp[node << 1] + std::min(dp[node << 1 | 1], w[node]);
            };
            dfs1(dfs1, node);
            return dp[node] <= k;
        };

        std::sort(leaves.begin(), leaves.end(),
                  [&](int x, int y) { return q[x] < q[y]; });
        int l = 0, r = leaves.size() - 1;
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (check(q[leaves[mid]])) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        assert(check(q[leaves[l]]));
        return leaves[l];
    };

    std::vector<int> ans;
    auto solve = [&](auto self, int node, i64 k) -> i64 {
        if (is_leaf(node)) {
            ans.push_back(q[node]);
            return k;
        }
        int t = get_sentinel(node, k);
        bool is_left = false;
        {
            int now = t;
            while ((now >> 1) > node) {
                now >>= 1;
            }
            is_left = (now == (node << 1));
        }

        if (!is_left) {
            i64 k_for_l = dp[node << 1];
            k_for_l += self(self, node << 1 | 1, k - k_for_l);
            return self(self, node << 1, k_for_l);
        } else {
            i64 k_for_r = dp[node] - dp[node << 1],
                dp_r = dp[node << 1 | 1];
            k_for_r += self(self, node << 1, k - k_for_r);
            if (k_for_r >= dp_r) {
                return self(self, node << 1 | 1, k_for_r);
            } else {
                return self(self, node << 1 | 1, k_for_r - w[node]);
            }
        }
    };
    solve(solve, 1, K);

    for (int i : ans) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
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