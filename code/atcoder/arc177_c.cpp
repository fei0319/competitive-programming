#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::string> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    const int D = 4;
    const int dx[D] = {1, -1, 0, 0};
    const int dy[D] = {0, 0, 1, -1};
    auto calc = [&](std::pair<int, int> s, std::pair<int, int> t,
                    char c) -> int {
        std::deque<std::pair<int, int>> q;
        q.push_back(s);

        std::vector<std::vector<int>> dist(n, std::vector<int>(n, -1));
        dist[s.first][s.second] = a[s.first][s.second] != c;

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop_front();
            for (int i = 0; i < D; ++i) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
                    continue;
                }
                if (dist[nx][ny] == -1) {
                    int w = a[nx][ny] != c;
                    dist[nx][ny] = dist[x][y] + w;
                    if (w == 0) {
                        q.push_front({nx, ny});
                    } else {
                        q.push_back({nx, ny});
                    }
                }
            }
        }

        return dist[t.first][t.second];
    };

    std::cout << calc({0, 0}, {n - 1, n - 1}, 'R') +
                     calc({0, n - 1}, {n - 1, 0}, 'B')
              << '\n';

    return 0;
}