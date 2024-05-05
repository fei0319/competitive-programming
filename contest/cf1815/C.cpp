#include <algorithm>
#include <cstdio>
#include <vector>

constexpr int maxn = 1.5e3 + 19, inf = 1e9;

int n, m;
std::vector<int> G[maxn];
std::vector<int> ans[maxn];

int dist[maxn];
void bfs(int src, int *dist) {
    for (int i = 1; i <= n; ++i)
        dist[i] = inf;
    dist[src] = 1;
    static int q[maxn], h, t;
    q[h = t = 0] = src;
    while (h <= t) {
        int node = q[h++];
        for (int to : G[node])
            if (dist[to] == inf) {
                dist[to] = dist[node] + 1;
                q[++t] = to;
            }
    }
}

void solve() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        G[i].clear();
    for (int i = 1; i <= m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[v].push_back(u);
    }

    bfs(1, dist);
    for (int i = 1; i <= n; ++i)
        if (dist[i] == inf) {
            puts("INFINITE");
            return;
        }

    for (int i = 1; i <= n; ++i)
        ans[i].clear();
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i)
        a[i] = i + 1;
    std::sort(a.begin(), a.end(), [](const int &x, const int &y) {
        return dist[x] < dist[y];
    });
    int tot = 0;
    for (int i : a) {
        for (int j = 1; j <= dist[i]; ++j)
            ans[j].push_back(i);
        tot += dist[i];
    }
    puts("FINITE");
    printf("%d\n", tot);
    for (int i = 1; i <= n; ++i)
        for (auto j = ans[i].rbegin(); j != ans[i].rend(); ++j)
            printf("%d ", *j);
    puts("");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
}