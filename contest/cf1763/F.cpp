#include <bits/stdc++.h>

constexpr int MAXN = 4e5 + 19, MAXB = 20;
int n, m;
std::vector<int> G[MAXN];

namespace bridge {
int dfn[MAXN], low[MAXN], ind;
int st[MAXN], top;
int col[MAXN], sz[MAXN], tot;

void dfs(int node, int f) {
    st[++top] = node;
    dfn[node] = low[node] = ++ind;
    for (int to : G[node]) {
        if (to == f) {
            continue;
        }
        if (dfn[to]) {
            low[node] = std::min(low[node], dfn[to]);
        } else {
            dfs(to, node);
            low[node] = std::min(low[node], low[to]);
        }
    }
    if (dfn[node] == low[node]) {
        ++tot;
        do {
            col[st[top]] = tot;
            top -= 1;
        } while (top && st[top + 1] != node);
    }
}

std::vector<int> E[MAXN];
int fa[MAXN][MAXB], dep[MAXN], dist[MAXN];
void dfs1(int node, int f) {
    fa[node][0] = f;
    dep[node] = dep[f] + 1;
    dist[node] = dist[f] + sz[node];
    for (int i = 1; i < MAXB && fa[node][i - 1]; ++i) {
        fa[node][i] = fa[fa[node][i - 1]][i - 1];
    }
    for (int to : E[node]) {
        if (to == f) {
            continue;
        }
        dfs1(to, node);
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) {
        std::swap(x, y);
    }
    for (int i = MAXB - 1; i >= 0; --i) {
        if (dep[fa[x][i]] >= dep[y]) {
            x = fa[x][i];
        }
    }
    if (x == y) {
        return x;
    }
    for (int i = MAXB - 1; i >= 0; --i) {
        if (fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}

void solve() {
    dfs(1, 0);
    for (int i = 1; i <= n; ++i) {
        for (int to : G[i]) {
            if (col[i] != col[to]) {
                E[col[i]].push_back(col[to]);
            } else {
                sz[col[i]] += 1;
            }
        }
    }
    for (int i = 1; i <= tot; ++i) {
        sz[i] /= 2;
    }
    dfs1(1, 0);
}

int count(int a, int b) {
    a = col[a];
    b = col[b];

    int x = lca(a, b);
    return dep[a] + dep[b] - dep[x] * 2;
}
} // namespace bridge

namespace cut_vertex {
int dfn[MAXN], low[MAXN], ind;
int st[MAXN], top;
int tot;
int sz[MAXN], ret[MAXN];
std::vector<int> E[MAXN];

void dfs(int node) {
    st[++top] = node;
    dfn[node] = low[node] = ++ind;
    for (int to : G[node]) {
        if (dfn[to]) {
            if (dfn[to] < dfn[node]) {
                ret[node] += 1;
            }
            low[node] = std::min(low[node], dfn[to]);
        } else {
            dfs(to);
            low[node] = std::min(low[node], low[to]);

            if (low[to] == dfn[node]) {
                ++tot;
                while (top && st[top + 1] != to) {
                    sz[n + tot] += ret[st[top]];

                    E[n + tot].push_back(st[top]);
                    E[st[top]].push_back(n + tot);
                    top -= 1;
                }
                E[n + tot].push_back(node);
                E[node].push_back(n + tot);
            }
        }
    }
}

int fa[MAXN][MAXB], dep[MAXN], dist[MAXN];
void dfs1(int node, int f) {
    fa[node][0] = f;
    dep[node] = dep[f] + 1;
    dist[node] = dist[f] + sz[node];
    for (int i = 1; i < MAXB && fa[node][i - 1]; ++i) {
        fa[node][i] = fa[fa[node][i - 1]][i - 1];
    }
    for (int to : E[node]) {
        if (to == f) {
            continue;
        }
        dfs1(to, node);
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) {
        std::swap(x, y);
    }
    for (int i = MAXB - 1; i >= 0; --i) {
        if (dep[fa[x][i]] >= dep[y]) {
            x = fa[x][i];
        }
    }
    if (x == y) {
        return x;
    }
    for (int i = MAXB - 1; i >= 0; --i) {
        if (fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}

void solve() {
    dfs(1);
    for (int i = n + 1; i <= n + tot; ++i) {
        sz[i] -= 2;
    }

    dfs1(1, 0);
}

int count(int a, int b) {
    int x = lca(a, b);
    return dep[a] + dep[b] - 2 * dep[x] + dist[a] + dist[b] - dist[x] -
           dist[fa[x][0]];
}
} // namespace cut_vertex

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        std::cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    bridge::solve();
    cut_vertex::solve();

    int q;
    std::cin >> q;
    while (q--) {
        int a, b;
        std::cin >> a >> b;
        std::cout << cut_vertex::count(a, b) - bridge::count(a, b) << '\n';
    }
}