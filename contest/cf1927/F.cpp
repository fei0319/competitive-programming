#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 2e5 + 19;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::pair<int, std::pair<int, int>>> edges;
    std::vector<std::vector<std::pair<int, int>>> G(n);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u -= 1, v -= 1;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }

    std::vector<uint8_t> vist(n);
    std::vector<std::pair<int, int>> stack;
    std::vector<int> id(n);
    std::function<void(int, int, int)> dfs = [&](int node, int from,
                                                 int weight) {
        vist[node] = true;
        stack.emplace_back(node, n);
        id[node] = stack.size() - 1;
        for (auto [to, w] : G[node]) {
            if (to == from)
                continue;
            if (!vist[to]) {
                dfs(to, node, w);
            } else {
                if (stack.back().second > id[to]) {
                    stack.back().second = id[to];
                }
                edges.emplace_back(w, std::make_pair(node, to));
            }
        }
        int x = stack.back().second;
        if (stack.size() - 1 > x) {
            edges.emplace_back(weight, std::make_pair(node, from));
        }
        stack.pop_back();
        if (!stack.empty() && stack.back().second > x) {
            stack.back().second = x;
        }
    };
    for (int i = 0; i < n; ++i) {
        if (!vist[i]) {
            dfs(i, -1, 0);
        }
    }

    auto [w, e] = *std::min_element(edges.begin(), edges.end());
    auto [u, v] = e;

    std::vector<int> ans{u};
    std::fill(vist.begin(), vist.end(), false);
    std::function<bool(int, int)> find = [&](int node, int from) {
        vist[node] = true;
        ans.push_back(node);
        for (auto [to, w] : G[node]) {
            if (to == from)
                continue;
            if (to == u) {
                return true;
            }
            if (!vist[to]) {
                if (find(to, node)) {
                    return true;
                }
            }
        }
        ans.pop_back();
        return false;
    };
    find(v, u);

    std::cout << w << ' ' << ans.size() << '\n';
    for (int i : ans) {
        std::cout << i + 1 << ' ';
    }
    std::cout << '\n';
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