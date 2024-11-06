// Problem: P8063 [BalkanOI 2012] Shortest paths
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8063
// Memory Limit: 256 MB
// Time Limit: 1500 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
typedef long long int ll;
template <typename Tp>
void chkmax(Tp &a, const Tp &b) {
    a = std::max(a, b);
}
template <typename Tp>
void chkmin(Tp &a, const Tp &b) {
    a = std::min(a, b);
}
template <typename Tp>
void read(Tp &res) {
    static char ch;
    ch = getchar(), res = 0;
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) res = res * 10 + ch - 48, ch = getchar();
}

const int maxn = 2e3 + 19, maxm = 1e5 + 19, inf = 1e9;

struct Edge {
    int to, next, dist;
} edge[maxm << 1];

int head[maxn], cnt;

inline void add(int from, int to, int dist) {
    edge[++cnt].to = to;
    edge[cnt].next = head[from];
    edge[cnt].dist = dist;
    head[from] = cnt;
}

int n, m, a, b, w[maxn][maxn];
int da[maxn], pa[maxn];
int db[maxn], pb[maxn];
int k, v[maxn], rnk[maxn], c[maxn], ans[maxn];

struct Node {
    int d, p, id;
    bool operator<(const Node &b) const {
        return d != b.d ? d > b.d : p > b.p;
    }
};

bool rev;
int get(int u, int v) {
    if (c[u] != v && c[v] != u) return 0;
    if (c[u] == v) return rev ? k - rnk[u] : rnk[u];
    else return rev ? k - rnk[v] : rnk[v];
}

void dijkstra(int s, int *d, int *p) {
    static bool vist[maxn];
    std::priority_queue<Node> q;
    for (int i = 1; i <= n; ++i) d[i] = inf, p[i] = inf, vist[i] = false;
    d[s] = p[s] = 0;
    q.push((Node){0, 0, s});
    while (!q.empty()) {
        auto node = q.top().id;
        q.pop();
        if (vist[node]) continue;
        vist[node] = true;
        for (int i = head[node]; i; i = edge[i].next) {
            int to = edge[i].to;
            if (d[to] > d[node] + edge[i].dist) {
                d[to] = d[node] + edge[i].dist;
                p[to] = std::max(p[node], get(node, to));
                q.push((Node){d[to], p[to], to});
            }
        }
    }
}

void update(int l, int r, int w) {
    for (int i = l; i <= r; ++i) chkmin(ans[i], w);
}

int main() {
    read(n), read(m), read(a), read(b);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) w[i][j] = (i == j ? 0 : inf);
    for (int i = 1, u, v, d; i <= m; ++i) {
        read(u), read(v), read(d);
        add(u, v, d), add(v, u, d);
        w[u][v] = std::min(w[u][v], d);
        w[v][u] = std::min(w[v][u], d);
    }
    read(k);
    for (int i = 1; i <= k; ++i) read(v[i]), rnk[v[i]] = i;
    for (int i = k; i > 1; --i) c[v[i - 1]] = v[i];
    dijkstra(a, da, pa), rev = true, dijkstra(b, db, pb);
    for (int i = 1; i <= k; ++i) ans[i] = inf;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            ll t = da[i] + db[j] + w[i][j];
            if (t >= inf || c[i] == j || c[j] == i) continue;
            //	printf("(%d, %d): %d %d %lld\n", i, j, pa[i] + 1, k - 1 -
            //pb[j],
            // t);
            update(pa[i] + 1, k - 1 - pb[j], t);
        }
    for (int i = 1; i < k; ++i) printf("%d\n", ans[i] < inf ? ans[i] : -1);
}