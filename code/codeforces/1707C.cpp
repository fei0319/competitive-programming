// Problem: C. DFS Trees
// Contest: Codeforces - Codeforces Round #808 (Div. 1)
// URL: https://codeforces.com/contest/1707/problem/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

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
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        res = res * 10 + ch - 48, ch = getchar();
}

const int maxn = 1e6 + 19;

int n, m, u[maxn], v[maxn];
std::vector<int> G[maxn];

struct UFS {
    int fa[maxn];
    int find(int x) {
        if (x != fa[x])
            fa[x] = find(fa[x]);
        return fa[x];
    }
    void merge(int x, int y) {
        x = find(x), y = find(y);
        fa[x] = y;
    }
    void init(void) {
        for (int i = 1; i <= n; ++i)
            fa[i] = i;
    }
} ufs;

int top[maxn], son[maxn], dep[maxn], size[maxn], fa[maxn];
void dfs1(int node, int f) {
    fa[node] = f, dep[node] = dep[f] + 1, size[node] = 1;
    for (int to : G[node])
        if (to != f) {
            dfs1(to, node);
            size[node] += size[to];
            if (size[to] > size[son[node]])
                son[node] = to;
        }
}
void dfs2(int node, int t) {
    top[node] = t;
    if (son[node])
        dfs2(son[node], t);
    for (int to : G[node])
        if (to != fa[node] && to != son[node])
            dfs2(to, to);
}
int lca(int x, int y) {
    while (top[x] != top[y])
        if (dep[top[x]] > dep[top[y]])
            x = fa[top[x]];
        else
            y = fa[top[y]];
    return dep[x] < dep[y] ? x : y;
}
int findSon(int x, int y) {
    while (top[x] != top[y]) {
        y = top[y];
        if (fa[y] == x)
            return y;
        else
            y = fa[y];
    }
    return son[x];
}

int kill[maxn];
bool ans[maxn];
void dfs(int node, int f) {
    kill[node] += kill[f];
    for (int to : G[node])
        if (to != f)
            dfs(to, node);
    if (!kill[node])
        ans[node] = true;
}

int main() {
    auto st = clock();
    read(n), read(m);
    for (int i = 1; i <= m; ++i)
        read(u[i]), read(v[i]);

    ufs.init();
    for (int i = 1; i <= m; ++i) {
        if (ufs.find(u[i]) != ufs.find(v[i])) {
            ufs.merge(u[i], v[i]);
            G[u[i]].push_back(v[i]);
            G[v[i]].push_back(u[i]);
        }
    }

    dfs1(1, 0);
    dfs2(1, 1);

    ufs.init();
    for (int i = 1; i <= m; ++i) {
        if (ufs.find(u[i]) != ufs.find(v[i])) {
            ufs.merge(u[i], v[i]);
        } else {
            int LCA = lca(u[i], v[i]);
            if (LCA == u[i] || LCA == v[i]) {
                if (dep[u[i]] > dep[v[i]])
                    std::swap(u[i], v[i]);
                ++kill[findSon(u[i], v[i])];
                --kill[v[i]];
            } else {
                ++kill[1];
                --kill[u[i]];
                --kill[v[i]];
            }
        }
    }

    dfs(1, 0);
    for (int i = 1; i <= n; ++i)
        putchar(ans[i] ? '1' : '0');
}

/*





















*/