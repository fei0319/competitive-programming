#ifdef ONLINE_JUDGE
#include <bits/stdc++.h>
#endif
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::vector<std::pair<int, int>>> adj(n * n + 2);
    auto coord = [&](int x, int y) -> int {
        if (x < 0 || y >= n) {
            return n * n;
        }
        if (x >= n || y < 0) {
            return n * n + 1;
        }
        return x * n + y;
    };

    for (int x = 0; x <= n; ++x) {
        for (int y = 0; y < n; ++y) {
            int v;
            std::cin >> v;
            adj[coord(x, y)].emplace_back(coord(x - 1, y), v);
        }
    }
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y <= n; ++y) {
            int v;
            std::cin >> v;
            adj[coord(x, y - 1)].emplace_back(coord(x, y), v);
        }
    }
    for (int x = 0; x <= n; ++x) {
        for (int y = 0; y < n; ++y) {
            int v;
            std::cin >> v;
            adj[coord(x - 1, y)].emplace_back(coord(x, y), v);
        }
    }
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y <= n; ++y) {
            int v;
            std::cin >> v;
            adj[coord(x, y)].emplace_back(coord(x, y - 1), v);
        }
    }

    const int s = coord(0, -1), t = coord(-1, 0);
    std::priority_queue<std::pair<int, int>> q;

    constexpr int INF = 2e9;
    std::vector<int> dist(n * n + 2, INF);
    std::vector<uint8_t> vist(n * n + 2);
    dist[s] = 0;
    q.push({-dist[s], s});

    while (!q.empty()) {
        int node = q.top().second;
        q.pop();

        if (vist[node]) {
            continue;
        }
        vist[node] = true;

        for (auto [to, w] : adj[node]) {
            if (dist[to] > dist[node] + w) {
                dist[to] = dist[node] + w;
                q.push({-dist[to], to});
            }
        }
    }

    std::cout << dist[t] << '\n';
}