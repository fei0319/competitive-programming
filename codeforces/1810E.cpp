#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

int n, m, a[maxn];
std::vector<int> G[maxn];
bool vist[maxn];

int bfs(int src) {
    static int tag[maxn], timer;
    std::priority_queue<std::pair<int, int>> q;
    ++timer;
    q.push({-a[src], src});
    int cnt = 0;
    while (!q.empty()) {
        int node = q.top().second;
        q.pop();
        if (tag[node] == timer)
            continue;
        if (a[node] > cnt)
            return cnt;
        tag[node] = timer, vist[node] = true, ++cnt;
        for (int to : G[node]) {
            if (tag[to] != timer) {
                q.push({-a[to], to});
            }
        }
    }
    return cnt;
}

void solve(void) {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        vist[i] = 0;
        G[i].clear();
    }

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];
    for (int i = 1; i <= m; ++i) {
        int u, v;
        std::cin >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i)
        if (a[i] == 0 && !vist[i]) {
            if (bfs(i) == n) {
                std::cout << "YES\n";
                return;
            }
        }
    std::cout << "NO\n";
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