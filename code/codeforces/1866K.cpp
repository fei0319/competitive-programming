#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 1e5 + 19, MAXS = 1e7 + 19, B = 18;
const ll INF = 1e18;

ll F(std::pair<int, ll> p, int k) { return (ll)k * p.first + p.second; }

class Lichao {
    static const int N = 1e9;
    static int tot;
    struct Node {
        int ls, rs;
        std::pair<int, ll> p;
        ll v;
    };
    static Node tr[MAXS];
    static void add(int &node, int L, int R, std::pair<int, ll> p,
                    bool f) {
        if (!node) {
            node = ++tot;
            tr[node].p = {-1, -INF};
            tr[node].v = -INF;
        }
        if (tr[node].p.first < 0) {
            tr[node].p = p;
            return;
        }
        if (L == R) {
            if (F(p, L) > F(tr[node].p, L)) {
                tr[node].v = F(tr[node].p, L);
                tr[node].p = p;
            } else {
                tr[node].v = std::max(tr[node].v, F(p, L));
            }
            return;
        }
        int mid = (L + R) / 2;
        if (F(p, mid) + F(p, mid + 1) >
            F(tr[node].p, mid) + F(tr[node].p, mid + 1)) {
            std::swap(p, tr[node].p);
        }

        bool cL = (F(p, L) >= F(tr[node].p, L)),
             cR = (F(p, R) >= F(tr[node].p, R));

        if ((cL && !cR)) {
            add(tr[node].ls, L, mid, p, true);
            if (f) {
                add(tr[node].rs, mid + 1, R, p, false);
            }
        }
        if ((!cL && cR)) {
            add(tr[node].rs, mid + 1, R, p, true);
            if (f) {
                add(tr[node].ls, L, mid, p, false);
            }
        }
        if ((!cL && !cR) || (cL && cR)) {
            if (f) {
                add(tr[node].rs, mid + 1, R, p, false);
                add(tr[node].ls, L, mid, p, false);
            }
        }
    }
    static std::pair<ll, ll> query(int node, int L, int R, int x) {
        if (!node) {
            return {-INF, -INF};
        }
        if (L == R) {
            return {F(tr[node].p, x), tr[node].v};
        }
        int mid = (L + R) / 2;
        std::pair<ll, ll> res = (x <= mid)
                                    ? query(tr[node].ls, L, mid, x)
                                    : query(tr[node].rs, mid + 1, R, x);
        ll v = F(tr[node].p, x);
        if (v > res.first) {
            res.second = res.first;
            res.first = v;
        } else if (v > res.second) {
            res.second = v;
        }
        return res;
    }

public:
    static void add(int &node, std::pair<int, ll> p) {
        //        std::cout << "add " << p.first << ' ' <<p.second << '\n';
        add(node, 1, N, p, true);
    }
    static ll query(int node, int k) {
        auto [u, v] = query(node, 1, N, k);
        return u + std::max(v, 0LL);
    }
};

using lc = Lichao;
int lc::tot = 0;
lc::Node lc::tr[MAXS];

int rt[MAXN];
int n, fa[MAXN][B];
std::vector<std::pair<int, int>> G[MAXN];
ll dep_w[MAXN];
int dep[MAXN];

std::pair<ll, int> dp[MAXN], g[MAXN];

void dfs1(int node, int f) {
    fa[node][0] = f;
    for (int i = 1; fa[node][i - 1]; ++i) {
        fa[node][i] = fa[fa[node][i - 1]][i - 1];
    }

    dp[node] = {0LL, node};

    for (auto [to, w] : G[node]) {
        if (to == f) continue;
        dep_w[to] = dep_w[node] + w;
        dep[to] = dep[node] + 1;
        dfs1(to, node);
        dp[node] = std::max(dp[node], {dp[to].first + w, dp[to].second});
    }
}

void dfs2(int node, int f) {
    int d = G[node].size();
    std::vector<std::pair<ll, int>> pre(d, {-INF, 0}), suf(d, {-INF, 0});

    for (int i = 1; i < d; ++i) {
        auto [to, w] = G[node][i - 1];
        if (to == f) {
            pre[i] = pre[i - 1];
            continue;
        }
        pre[i] = std::max(pre[i - 1], {dp[to].first + w, dp[to].second});
    }
    for (int i = d - 2; i >= 0; --i) {
        auto [to, w] = G[node][i + 1];
        if (to == f) {
            suf[i] = suf[i + 1];
            continue;
        }
        suf[i] = std::max(suf[i + 1], {dp[to].first + w, dp[to].second});
    }

    for (int i = 0; i < d; ++i) {
        auto [to, w] = G[node][i];
        if (to == f) continue;
        g[to] = std::max({pre[i], suf[i], g[node], {0LL, node}});
        g[to].first += w;
        dfs2(to, node);
    }

    // std::cout << node << '\n';
    for (auto [to, w] : G[node]) {
        if (to == f) {
            lc::add(rt[node], {w, g[node].first - w});
            continue;
        }
        lc::add(rt[node], {w, dp[to].first});
        dp[to] = std::max(dp[to], g[to]);
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) {
        std::swap(x, y);
    }
    for (int i = B - 1; i >= 0; --i) {
        if (dep[fa[x][i]] >= dep[y]) {
            x = fa[x][i];
        }
    }
    if (x == y) {
        return x;
    }
    for (int i = B - 1; i >= 0; --i) {
        if (fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}

ll dist(int x, int y) {
    return dep_w[x] + dep_w[y] - 2 * dep_w[lca(x, y)];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 2; i <= n; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }

    std::fill(g, g + n + 1, std::make_pair(-INF, 0));
    dep[1] = 1;
    dfs1(1, 0);
    dfs2(1, 0);

    int q;
    std::cin >> q;
    while (q--) {
        int x, k;
        std::cin >> x >> k;

        ll res = lc::query(rt[x], k);
        int y = dp[x].second, z = dp[y].second;
        if (dist(y, z) != dist(y, x) + dist(x, z)) {
            res = std::max(res, dist(y, z));
        }

        std::cout << res << '\n';
    }

    return 0;
}