#include <bits/stdc++.h>

using ll = long long int;

constexpr int D = 4, dx[D] = {1, 0, -1, 0}, dy[D] = {0, 1, 0, -1};

void solve() {
    int n;
    std::cin >> n;

    std::string s[2];
    std::cin >> s[0] >> s[1];

    std::vector<std::vector<int>> G(n * 2);

    auto next = [&](int x, int y) {
        if (s[x][y] == '<') {
            return std::make_pair(x, y - 1);
        } else {
            return std::make_pair(x, y + 1);
        }
    };

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int d = 0; d < D; ++d) {
                int x = i + dx[d], y = j + dy[d];
                if (x >= 0 && x < 2 && y >= 0 && y < n) {
                    auto [nx, ny] = next(x, y);
                    G[i * n + j].push_back(nx * n + ny);
                }
            }
        }
    }

    std::vector<uint8_t> vist(n * 2);
    std::function<bool(int)> dfs = [&](int node) {
        if (node == n * 2 - 1) {
            return true;
        }

        if (vist[node]) {
            return false;
        }
        vist[node] = true;

        for (int to : G[node]) {
            if (dfs(to)) {
                return true;
            }
        }
        return false;
    };

    std::cout << (dfs(0) ? "YES\n" : "NO\n");
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