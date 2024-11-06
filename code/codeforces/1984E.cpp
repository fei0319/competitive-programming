#include <bits/stdc++.h>

using i64 = int64_t;

void solve() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> adj(n + 1);
    for (int i = 2; i <= n; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (n == 2) {
        std::cout << "2\n";
        return;
    }

    std::vector<std::array<int, 2>> f(n + 1), g(n + 1);
    auto dfs = [&](auto self, int node, int fa) -> void {
        if (adj[node].size() == 1) {
            f[node][0] = 0;
            f[node][1] = 1;
            g[node][0] = 1;
            g[node][1] = 1;
            return;
        }
        for (int to : adj[node]) {
            if (to == fa) {
                continue;
            }
            self(self, to, node);

            std::array<int, 2> nf{}, ng{};

            nf[0] = f[node][0] + f[to][1];
            ng[0] = std::max(g[node][0] + f[to][1], f[node][0] + g[to][1]);

            nf[1] = f[node][1] + f[to][0];
            ng[1] = std::max(g[node][1] + f[to][0], f[node][1] + g[to][0]);

            f[node] = nf;
            g[node] = ng;
        }

        f[node][1] = std::max(f[node][0], f[node][1] + 1);
        g[node][1] = std::max(g[node][0], g[node][1] + 1);

        // std::cout << "f_" << node << " = " << f[node][0] << ' ' <<
        // f[node][1]
        //           << '\n';
        // std::cout << "g_" << node << " = " << g[node][0] << ' ' <<
        // g[node][1]
        //           << '\n';
    };

    int rt = 1;
    while (adj[rt].size() == 1) {
        ++rt;
    }

    dfs(dfs, rt, 0);
    std::cout << g[rt][1] << '\n';
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