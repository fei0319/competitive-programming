#include <bits/stdc++.h>

const int MAXN = 1e3 + 5;

int n, m;
std::vector<int> G[MAXN];
int deg[MAXN];

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

int main() {
    std::cin >> n >> m;

    std::iota(fa + 1, fa + 1 + n, 1);
    std::fill(sz + 1, sz + 1 + n, 1);

    for (int i = 1; i <= m; ++i) {
        int u, v;
        std::cin >> u >> v;

        G[v].push_back(u);
        merge(u, v);
    }

    std::vector<int> indices;
    std::vector<std::vector<int>> components(n + 1);

    for (int i = 1; i <= n; ++i) {
        if (i == getf(i) && sz[i] > 1) {
            indices.push_back(i);
        }
        if (sz[getf(i)] > 1) {
            components[getf(i)].push_back(i);
        }
    }

    std::vector<std::pair<int, int>> ans;
    std::function<void(int, const std::vector<int> &)> add =
        [&](int x, const std::vector<int> &v) {
            if (x) {
                ans.emplace_back(x, v.front());
            }
            for (int i = 1; i < (int)v.size(); ++i) {
                ans.emplace_back(v[i - 1], v[i]);
            }
        };

    for (const auto &component : components) {
        std::function<std::pair<bool, std::vector<int>>(int)> check =
            [&](int x) {
                for (int i : component) {
                    deg[i] = 0;
                }
                for (int i : component) {
                    if (i == x) continue;
                    for (int to : G[i]) {
                        deg[to] += 1;
                    }
                }

                std::queue<int> q;
                for (int i : component) {
                    if (deg[i] == 0) {
                        q.push(i);
                    }
                }

                std::vector<int> res;
                while (!q.empty()) {
                    int node = q.front();
                    q.pop();

                    res.push_back(node);

                    if (node != x) {
                        for (int to : G[node]) {
                            deg[to] -= 1;
                            if (deg[to] == 0) {
                                q.push(to);
                            }
                        }
                    }
                }

                if (res.size() == component.size()) {
                    return std::make_pair(true, res);
                }
                return std::make_pair(false, std::vector<int>{});
            };
        if (check(0).first) {
            add(0, check(0).second);
            continue;
        }
        bool flag = false;
        for (int i : component) {
            auto [validity, result] = check(i);
            if (validity) {
                add(i, result);
                flag = true;
                break;
            }
        }
        if (!flag) {
            std::cout << "-1\n";
            return 0;
        }
    }

    std::reverse(ans.begin(), ans.end());
    std::cout << ans.size() << '\n';
    for (auto [u, v] : ans) {
        std::cout << v << ' ' << u << '\n';
    }
}