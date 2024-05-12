#include <bits/stdc++.h>

using ll = long long int;

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<std::vector<int>> G(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        u -= 1, v -= 1;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    auto check = [&](int x) {
        std::vector<int> a(n);
        int tot = 0;
        std::function<void(int, int)> dfs = [&](int node, int f) {
            a[node] = 1;
            for (int to : G[node]) {
                if (to != f) {
                    dfs(to, node);
                    a[node] += a[to];
                }
            }
            if (a[node] >= x) {
                tot += 1;
                a[node] = 0;
            }
        };
        dfs(0, -1);
        return tot >= k + 1;
    };

    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    std::cout << l << '\n';
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