#include <bits/stdc++.h>

const int MAXN = 1e6 + 19;
const int INF = 1e9;
const int dx[]{1, -1, 0, 0}, dy[]{0, 0, 1, -1};

class TwoMin {
    std::vector<std::pair<int, int>> a;

public:
    bool insert(const std::pair<int, int> &p) {
        if (a.empty()) {
            a.push_back(p);
            return true;
        } else if (a.size() == 1 && a[0].second != p.second) {
            a.push_back(p);
            return true;
        } else if (a.size() == 2 && a[0].second != p.second && p < a[1]) {
            a[1] = p;
            return true;
        }
        return false;
    }
    std::pair<int, int> next(int index) const {
        return {a[index].first + 1, a[index].second};
    }
    std::size_t size() const {
        return a.size();
    }
    int sum(int index) const {
        int res = 0;
        for (int i = 0; i < index; ++i) {
            res += a[i].first;
        }
        return res;
    }
};

int n, m;
std::vector<std::string> a;

int id(int x, int y) {
    return x * m + y;
}

int fa[MAXN], sz[MAXN];
int getf(int node) {
    return fa[node] == node ? node : fa[node] = getf(fa[node]);
}
void merge(int x, int y) {
    x = getf(x), y = getf(y);
    if (x != y) {
        fa[x] = y;
        sz[y] += sz[x];
    }
}

bool at_verge(int x, int y) {
    return x == 0 || x == n - 1 || y == 0 || y == m - 1;
}
bool is_empty(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && (a[x][y] == '.' || a[x][y] == 'V');
}

TwoMin dp[MAXN];
int dist[MAXN];
std::vector<int> dep[MAXN];

void solve() {
    std::cin >> n >> m;
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::iota(fa + 0, fa + n * m, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            sz[id(i, j)] = at_verge(i, j) && is_empty(i, j);
        }
    }

    int empty_cnt = 0, sx = 0, sy = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (is_empty(i, j)) {
                empty_cnt += 1;
                for (int d = 0; d < 4; ++d) {
                    int nx = i + dx[d], ny = j + dy[d];
                    if (is_empty(nx, ny)) {
                        merge(id(i, j), id(nx, ny));
                    }
                }
            }
            if (a[i][j] == 'V') {
                sx = i;
                sy = j;
            }
        }
    }

    if (sz[getf(id(sx, sy))] == 0) {
        std::cout << empty_cnt - 1 << '\n';
        return;
    }

    std::fill(dist + 0, dist + n * m, INF);
    std::queue<int> q;
    dist[id(sx, sy)] = 0;
    q.push(id(sx, sy));

    int max_dep = 0;
    while (!q.empty()) {
        int x = q.front() / m, y = q.front() % m;
        q.pop();
        max_dep = std::max(max_dep, dist[id(x, y)]);

        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (is_empty(nx, ny) && dist[id(nx, ny)] == INF) {
                dist[id(nx, ny)] = dist[id(x, y)] + 1;
                q.push(id(nx, ny));
            }
        }
    }
    for (int i = 0; i <= max_dep; ++i) {
        dep[i].clear();
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (dist[id(i, j)] != INF) {
                dep[dist[id(i, j)]].push_back(id(i, j));
            }
        }
    }

    if (sz[getf(id(sx, sy))] == 1) {
        for (int i = 0; i <= max_dep; ++i) {
            for (int j : dep[i]) {
                if (at_verge(j / m, j % m)) {
                    std::cout << empty_cnt - 1 - i << '\n';
                    return;
                }
            }
        }
        assert(false);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            dp[id(i, j)] = TwoMin{};
            if (dist[id(i, j)] != INF && at_verge(i, j)) {
                dp[id(i, j)].insert({0, id(i, j)});
                q.push(id(i, j));
            }
        }
    }
    while (!q.empty()) {
        int x = q.front() / m, y = q.front() % m;
        q.pop();

        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (is_empty(nx, ny)) {
                bool flag = false;
                for (int i = 0; i < dp[id(x, y)].size(); ++i) {
                    if (dp[id(nx, ny)].insert(dp[id(x, y)].next(i))) {
                        flag = true;
                    }
                }
                if (flag) {
                    q.push(id(nx, ny));
                }
            }
        }
    }

    int ans = INF;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (dist[id(i, j)] != INF) {
                ans = std::min(ans, dist[id(i, j)] + dp[id(i, j)].sum(2));
            }
        }
    }
    std::cout << empty_cnt - ans - 1 << '\n';
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