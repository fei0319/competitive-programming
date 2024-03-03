#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 1e6 + 19;

bool comp(const std::vector<int> &a, const std::vector<int> &b) {
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] <= b[i]) {
            return true;
        }
    }
    return false;
}

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> c(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> c[i];
    }

    std::vector<std::vector<int>> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        a[i].resize(m + 1);
        for (int j = 1; j <= m; ++j) {
            std::cin >> a[i][j];
        }
    }

    std::vector<std::vector<std::pair<int, int>>> G(n * 2 + n * m + 1);
    auto add = [&](int u, int v, int w) { G[u].emplace_back(v, w); };
    auto dijkstra = [&](auto &G, int src, int t) -> ll {
        std::vector<ll> dist(G.size(), ll(1e18));
        std::vector<uint8_t> vist(G.size(), false);
        dist[src] = 0;

        std::priority_queue<std::pair<ll, int>> q;
        q.emplace(0LL, src);

        while (!q.empty()) {
            auto [_, node] = q.top();
            q.pop();
            if (vist[node]) {
                continue;
            }
            vist[node] = true;

            for (auto [to, w] : G[node]) {
                if (dist[to] > dist[node] + w) {
                    dist[to] = dist[node] + w;
                    q.emplace(-dist[to], to);
                }
            }
        }

        return dist[t];
    };

    for (int i = 1; i <= n; ++i) {
        add(i, i + n, c[i]);
    }

    for (int b = 1; b <= m; ++b) {
        std::vector<int> id;
        for (int i = 1; i <= n; ++i) {
            id.push_back(i);
        }
        std::sort(id.begin(), id.end(),
                  [&](int x, int y) { return a[x][b] < a[y][b]; });

        int d = n * 2 + n * (b - 1);
        std::vector<int> v;
        for (int l = 0, r; l < n; l = r + 1) {
            r = l;
            while (r + 1 < n && a[id[r]][b] == a[id[r + 1]][b]) {
                ++r;
            }
            for (int i = l; i <= r; ++i) {
                add(id[l] + d, id[i], 0);
                add(id[i] + n, id[l] + d, 0);
            }

            v.push_back(id[l]);
        }

        for (int i = 0; i + 1 < v.size(); ++i) {
            add(v[i] + d, v[i + 1] + d, 0);
            add(v[i + 1] + d, v[i] + d, a[v[i + 1]][b] - a[v[i]][b]);
        }
    }

    std::cout << dijkstra(G, 1 + n, n + n) << '\n';
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