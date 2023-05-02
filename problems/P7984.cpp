// Problem: P7984 [USACO21DEC]  Tickets P
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7984
// Memory Limit: 256 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
typedef long long int ll;
template <typename Tp> void chkmax(Tp &a, const Tp &b) { a = std::max(a, b); }
template <typename Tp> void chkmin(Tp &a, const Tp &b) { a = std::min(a, b); }
template <typename Tp> void read(Tp &res) {
    static char ch;
    ch = getchar(), res = 0;
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        res = res * 10 + ch - 48, ch = getchar();
}

const int maxn = 1e5 + 19, maxm = maxn * 4;
const ll inf = 1e18;

ll f[maxm], g[maxm], dp[maxm];
int id[maxn];

std::vector<std::pair<int, std::pair<int, int>>> tik[maxn];
int n, k;

struct Edge {
    int to, next, dist;
} edge[maxn * 60];
int head[maxm], cnt;
inline void add(int from, int to, int dist) {
    edge[++cnt].next = head[from];
    head[from] = cnt;
    edge[cnt].to = to, edge[cnt].dist = dist;
}

int tot;
void build(int node, int L, int R) {
    chkmax(tot, node);
    if (L == R) {
        id[L] = node;
        return;
    }
    int mid = (L + R) >> 1;
    add(node << 1, node, 0), add(node << 1 | 1, node, 0);
    build(node << 1, L, mid), build(node << 1 | 1, mid + 1, R);
}

int __to, __dist;
void modify(int node, int L, int R, int l, int r) {
    if (l <= L && R <= r) {
        add(node, __to, __dist);
        return;
    }
    int mid = (L + R) >> 1;
    if (l <= mid)
        modify(node << 1, L, mid, l, r);
    if (r > mid)
        modify(node << 1 | 1, mid + 1, R, l, r);
}

struct Node {
    int to;
    ll dist;
    Node(int __to, ll __dist) { to = __to, dist = __dist; }
    bool operator<(const Node &b) const { return dist > b.dist; }
};

void dijkstra(ll *d) {
    static bool vist[maxm];
    std::priority_queue<Node> q;
    for (int i = 1; i <= tot; ++i) {
        vist[i] = false;
        if (d[i] != inf) {
            q.emplace(i, d[i]);
        }
    }
    while (!q.empty()) {
        int node = q.top().to;
        q.pop();
        if (vist[node])
            continue;
        vist[node] = true;
        for (int i = head[node]; i; i = edge[i].next)
            if (d[edge[i].to] > d[node] + edge[i].dist) {
                d[edge[i].to] = d[node] + edge[i].dist;
                q.emplace(edge[i].to, d[edge[i].to]);
            }
    }
}

struct SegmentTree {
    ll tr[maxm];
    int m;
    void init(void) {
        m = 1;
        while (m <= n)
            m <<= 1;
    }
    void build(void) {
        for (int i = m - 1; i >= 1; --i)
            tr[i] = std::min(tr[i << 1], tr[i << 1 | 1]);
    }
    ll query(int l, int r) {
        ll res = inf;
        for (l += m - 1, r += m + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
            if (l & 1 ^ 1)
                chkmin(res, tr[l ^ 1]);
            if (r & 1)
                chkmin(res, tr[r ^ 1]);
        }
        return res;
    }
} mf, mg;

int main() {
    read(n), read(k);
    build(1, 1, n);
    for (int i = 1, c, p, a, b; i <= k; ++i) {
        read(c), read(p), read(a), read(b);
        tik[c].emplace_back(p, std::make_pair(a, b));
        __to = id[c], __dist = p;
        modify(1, 1, n, a, b);
    }
    for (int i = 1; i <= tot; ++i)
        f[i] = g[i] = dp[i] = inf;
    f[id[1]] = g[id[n]] = 0ll;
    dijkstra(f), dijkstra(g);

    mf.init(), mg.init();
    for (int i = 1; i <= n; ++i) {
        mf.tr[mf.m + i] = f[id[i]];
        mg.tr[mg.m + i] = g[id[i]];
    }
    mf.build(), mg.build();
    for (int i = 1; i <= n; ++i) {
        chkmin(dp[id[i]], f[id[i]] + g[id[i]]);
        for (auto t : tik[i]) {
            int p = t.first, l = t.second.first, r = t.second.second;
            chkmin(dp[id[i]], mf.query(l, r) + mg.query(l, r) + p);
        }
    }
    dijkstra(dp);
    for (int i = 1; i <= n; ++i)
        if (dp[id[i]] < inf)
            std::printf("%lld\n", dp[id[i]]);
        else
            std::puts("-1");
}