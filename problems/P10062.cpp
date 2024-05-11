#include <bits/stdc++.h>

struct BipartiteColoring {
    std::vector<std::pair<int, int>> edge;
    std::vector<std::vector<int>> adj;
    std::vector<int> color;
    BipartiteColoring(int n) : adj(n) {}
    int add_edge(int u, int v) {
        edge.emplace_back(u, v);
        return edge.size() - 1;
    }
    int operator()() {
        const int n = adj.size();
        std::vector<int> deg(n);

        for (auto [u, v] : edge) {
            ++deg[u];
            ++deg[v];
        }

        const int d = *std::max_element(deg.begin(), deg.end());
        adj.assign(n, std::vector<int>(d, -1));

        for (int i = 0; i < edge.size(); ++i) {
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
                int n_id = adj[y][cx];
                if (n_id == -1) {
                    adj[x][cx] = adj[y][cx] = id;
                    break;
                }
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

        color.resize(edge.size());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < d; ++j) {
                if (adj[i][j] != -1) {
                    color[adj[i][j]] = j;
                }
            }
        }
        return d;
    }
};

void transpose(auto &a) {
    const int n = a.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            std::swap(a[i][j], a[j][i]);
        }
    }
}

void solve() {
    int n, r, c;
    std::cin >> n >> r >> c;

    std::vector<std::vector<int>> a(n + 1, std::vector<int>(n + 1));
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            std::cin >> a[i][j];
        }
    }

    bool flag = false;
    if (r < c) {
        std::swap(r, c);
        transpose(a);
        flag = true;
    }

    if (c < n) {
        BipartiteColoring bc(r + n + 1);
        std::map<std::pair<int, int>, int> match;
        for (int i = 1; i <= r; ++i) {
            std::vector<uint8_t> used(n + 1);
            for (int j = 1; j <= c; ++j) {
                used[a[i][j]] = true;
            }
            for (int j = 1; j <= n; ++j) {
                if (!used[j]) {
                    match[{i, j}] = bc.add_edge(i, r + j);
                }
            }
        }
        if (bc() != n - c) {
            std::cout << "No\n";
            return;
        }
        for (auto [p, id] : match) {
            a[p.first][bc.color[id] + c + 1] = p.second;
        }
    }

    BipartiteColoring bc(n + n + 1);
    std::map<std::pair<int, int>, int> match;
    for (int i = 1; i <= n; ++i) {
        std::vector<int> used(n + 1);
        for (int j = 1; j <= r; ++j) {
            used[a[j][i]] = true;
        }
        for (int j = 1; j <= n; ++j) {
            if (!used[j]) {
                match[{i, j}] = bc.add_edge(i, n + j);
            }
        }
    }
    assert(bc() == n - r);
    for (auto [p, id] : match) {
        a[bc.color[id] + r + 1][p.first] = p.second;
    }

    if (flag) {
        transpose(a);
    }

    std::cout << "Yes\n";
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cout << a[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}