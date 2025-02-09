// Problem: C - Lights Out on Tree
// Contest: AtCoder - AtCoder Regular Contest 148
// URL: https://atcoder.jp/contests/arc148/tasks/arc148_c
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
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

const int maxn = 2e5 + 19;
std::vector<int> G[maxn], E[maxn];
int n, q, m;
std::vector<int> S;
int st[maxn];

int dfn[maxn], ind;
int top[maxn], son[maxn], dep[maxn], size[maxn], fa[maxn];
bool col[maxn];
void dfs1(int node, int f) {
    dfn[node] = ++ind;
    fa[node] = f, dep[node] = dep[f] + 1, size[node] = 1;
    for (int to : G[node])
        if (to != f) {
            dfs1(to, node);
            size[node] += size[to];
            if (size[to] > size[son[node]]) son[node] = to;
        }
}
void dfs2(int node, int t) {
    top[node] = t;
    if (son[node]) dfs2(son[node], t);
    for (int to : G[node])
        if (to != fa[node] && to != son[node]) dfs2(to, to);
}
int lca(int x, int y) {
    while (top[x] != top[y])
        if (dep[top[x]] > dep[top[y]]) x = fa[top[x]];
        else
            y = fa[top[y]];
    return dep[x] < dep[y] ? x : y;
}

int dp[maxn][2];
void dfs(int node) {
    int t[] = {0, G[node].size() - E[node].size()};
    for (int to : E[node]) {
        dfs(to);
        if ((dep[to] - dep[node]) == 1)
            t[0] += dp[to][0], t[1] += dp[to][1];
        else
            t[0] += dp[to][0], t[1] += dp[to][0] + 1;
    }
    if (col[node]) {
        dp[node][0] = t[1] + 1;
        dp[node][1] = t[1];
    } else {
        dp[node][0] = t[0];
        dp[node][1] = t[0] + 1;
    }
    E[node].clear(), col[node] = false;
}

int main() {
    read(n), read(q);
    for (int i = 2, p; i <= n; ++i) {
        read(p);
        G[p].push_back(i);
    }
    dfs1(1, 0), dfs2(1, 1);
    while (q--) {
        read(m);
        S.resize(m);
        for (int i = 0; i < m; ++i) read(S[i]), col[S[i]] = true;
        std::sort(S.begin(), S.end(), [](const int &a, const int &b) {
            return dfn[a] < dfn[b];
        });
        int top;
        st[top = 1] = 1;
        for (int i = 0; i < m; ++i) {
            if (S[i] == 1) continue;
            int x = lca(S[i], st[top]);
            while (dep[st[top]] > dep[x]) {
                if (dep[st[top - 1]] > dep[x])
                    E[st[top - 1]].push_back(st[top]);
                else
                    E[x].push_back(st[top]);
                --top;
            }
            if (st[top] != x) st[++top] = x;
            st[++top] = S[i];
        }
        for (int i = 1; i < top; ++i) E[st[i]].push_back(st[i + 1]);
        // for(int i = 1; i <= n; ++i){
        // printf("%d:", i);
        // for(int j : E[i]) printf("%d ", j);
        // puts("");
        // }
        dfs(1);
        printf("%d\n", dp[1][0]);
    }
}