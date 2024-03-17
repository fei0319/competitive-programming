#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 2e3 + 19;

int n;
std::vector<int> G[MAXN];

void solve() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        G[i].clear();
    }
    for (int i = 2; i <= n; ++i) {
        int u, v;
        std::cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    std::vector<uint8_t> vist(n + 1, false);
    std::vector<std::pair<int, int>> ans;
    std::vector<int> fa(n + 1), dep(n + 1);

    std::function<std::pair<int, int>(int, int)> dfs = [&](int node, int f) {
        fa[node] = f;

        std::pair<int, int> res {1, node};
        for (int to : G[node]) {
            if (to != f) {
                dep[to] = dep[node] + 1;
                auto p = dfs(to, node);
                p.first += 1;
                res = std::max(res, p);
            }
        }
        return res;
    };

    {
        auto p = dfs(1, 0);
        auto q = dfs(p.second, 0);

        int u = p.second, v = q.second, len = q.first;
        //std::cout << u << ' ' << v << ' ' << len << '\n';

        if (len % 4 != 0) {
            int mid = v;
            for (int i = 1; i <= len / 2; ++i) {
                mid = fa[mid];
            }
            for (int i = 0; i <= len / 2; ++i) {
                ans.emplace_back(mid, i);
            }
        } else {
            int mid1 = v, mid2;
            for (int i = 1; i < len / 2; ++i) {
                mid1 = fa[mid1];
            }
            mid2 = fa[mid1];

            for (int i = 1; i < len / 2; i += 2) {
                ans.emplace_back(mid1, i);
                ans.emplace_back(mid2, i);
            }
        }

    }

    std::cout << ans.size() << '\n';
    for (auto [x, y] : ans) {
        std::cout << x << " " << y << "\n";
    }
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