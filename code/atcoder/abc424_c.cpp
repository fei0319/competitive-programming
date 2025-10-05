#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    std::vector<uint8_t> vis(n + 1);
    std::vector<int> layer;

    std::vector<std::vector<int>> adj(n + 1);
    for (int i = 1; i <= n; ++i) {
        int a, b;
        std::cin >> a >> b;

        if (a == 0) {
            vis[i] = true;
            layer.push_back(i);
        } else {
            adj[a].push_back(i);
            adj[b].push_back(i);
        }
    }

    while (!layer.empty()) {
        std::vector<int> next_layer;
        for (int x : layer) {
            for (int to : adj[x]) {
                if (!vis[to]) {
                    vis[to] = true;
                    next_layer.push_back(to);
                }
            }
        }
        std::swap(layer, next_layer);
    }

    std::cout << std::count(vis.begin(), vis.end(), true) << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();
}
