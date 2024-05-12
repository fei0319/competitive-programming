#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int a, b, m;
    std::cin >> a >> b >> m;

    std::vector<int> deg(a + b);
    std::vector<std::pair<int, int>> edge;
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        v += a;
        ++deg[u], ++deg[v];
        edge.emplace_back(u, v);
    }

    int d = *std::max_element(deg.begin(), deg.end());

    std::vector<std::vector<int>> adj(a + b, std::vector<int>(d, -1));
    for (int i = 0; i < m; ++i) {
        int id = i;
        auto [x, y] = edge[id];
        int cx = 0, cy = 0;
        while (adj[x][cx] != -1) {
            ++cx;
        }
        while (adj[y][cy] != -1) {
            ++cy;
        }
        while (id != -1) {
            if (adj[y][cx] == -1) {
                adj[x][cx] = adj[y][cx] = id;
                break;
            }

            int n_id = adj[y][cx];
            auto [n_x, n_y] = edge[n_id];
            if (n_x != y) {
                std::swap(n_x, n_y);
            }

            adj[n_x][cx] = adj[n_y][cx] = -1;
            adj[x][cx] = adj[y][cx] = id;

            id = n_id;
            x = n_x, y = n_y;
            std::swap(cx, cy);
        }
    }

    std::vector<int> color(m);
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < d; ++j) {
            if (adj[i][j] != -1) {
                color[adj[i][j]] = j + 1;
            }
        }
    }
    std::cout << d << '\n';
    for (int i = 0; i < m; ++i) {
        std::cout << color[i] << ' ';
    }

    return 0;
}