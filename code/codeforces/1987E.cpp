#include <bits/stdc++.h>

using i64 = int64_t;
constexpr i64 INF = 1e18;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int &i : a) {
        std::cin >> i;
    }

    std::vector<std::vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int p;
        std::cin >> p;
        p -= 1;

        adj[p].push_back(i);
    }

    i64 ans = 0;
    std::vector<std::vector<i64>> cap(n);
    auto dfs = [&](auto self, int node) -> void {
        i64 sum = 0;
        int sz = 0;
        for (int to : adj[node]) {
            self(self, to);
            sum += a[to];
            sz = std::max<int>(sz, cap[to].size());
        }

        cap[node].resize(sz + 1);
        for (int to : adj[node]) {
            for (int i = 0; i < cap[to].size(); ++i) {
                cap[node][i + 1] += cap[to][i];
                if (cap[node][i + 1] > INF) {
                    cap[node][i + 1] = INF;
                }
            }
            std::vector<i64> tmp;
            tmp.swap(cap[to]);
        }

        if (adj[node].empty()) {
            cap[node][0] = INF;
        } else if (a[node] <= sum) {
            cap[node][0] = sum - a[node];
        } else {
            int x = a[node] - sum;
            for (int i = 1; i <= sz && x; ++i) {
                int f = std::min<i64>(x, cap[node][i]);
                x -= f;
                cap[node][i] -= f;
                ans += (i64)f * i;
            }
        }
    };
    dfs(dfs, 0);

    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
}