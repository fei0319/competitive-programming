#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 1e5 + 19, INF = 1e9;

int n, m, q;
std::vector<int> G[MAXN];
int u[MAXN], v[MAXN];
int ans[MAXN];

int bfs(int src) {
    static int dist[MAXN];
    static int q[MAXN], h, t;
    std::fill(dist + 1, dist + 1 + n, INF);

    dist[src] = 0;
    q[h = t = 0] = src;

    while (h <= t) {
        int node = q[h++];
        for (int to : G[node]) {
            if (dist[to] == INF) {
                dist[to] = dist[node] + 1;
                q[++t] = to;
            }
        }
    }

    return *std::max_element(dist + 1, dist + 1 + n);
}

int d_G(int x) {
    for (int i = 1; i <= x; ++i) {
        G[u[i]].push_back(v[i]);
        G[v[i]].push_back(u[i]);
    }

    int res = bfs(1);

    for (int i = x; i >= 1; --i) {
        G[u[i]].pop_back();
        G[v[i]].pop_back();
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m >> q;
    for (int i = 1; i <= m; ++i) {
        int x, y;
        std::cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for (int i = 1; i <= q; ++i) {
        std::cin >> u[i] >> v[i];
    }

    int now = 0;

    while (now <= q) {
        ans[now] = d_G(now);

        int l = now, r = q;
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (ans[now] <= d_G(mid) * 2) l = mid;
            else
                r = mid - 1;
        }

        for (int i = now; i <= l; ++i) {
            ans[i] = ans[now];
        }

        now = l + 1;
    }

    for (int i = 0; i <= q; ++i) {
        std::cout << ans[i] << ' ';
    }

    return 0;
}