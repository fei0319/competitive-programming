// Problem: D. Edge Split
// Contest: Codeforces Round #819 (Div. 1 + Div. 2) and Grimoire of Code Annual
// Contest 2022 URL: https://codeforces.com/contest/1726/problem/D Memory Limit:
// 256 MB Time Limit: 2000 ms
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

const int maxn = 2e5 + 19;

int n, m;
std::vector<int> G[maxn];
std::mt19937 rng(std::time(0));

int myRnd(int l, int r) { return l + rng() % (r - l + 1); }

bool vist[maxn];
int fa[maxn], u[maxn], v[maxn];
void dfs(int node) {
    vist[node] = true, std::shuffle(G[node].begin(), G[node].end(), rng);
    for (int to : G[node])
        if (!vist[to])
            fa[to] = node, dfs(to);
}

bool ans[maxn];

void sov() {
    read(n), read(m);
    for (int i = 1; i <= n; ++i)
        G[i].clear();
    for (int i = 1; i <= m; ++i) {
        read(u[i]), read(v[i]);
        G[u[i]].push_back(v[i]), G[v[i]].push_back(u[i]);
    }
    if (m == n - 1) {
        for (int i = 1; i <= m; ++i)
            putchar('0');
        puts("");
        return;
    }
    while (true) {
        int rt = myRnd(1, n);
        for (int i = 1; i <= n; ++i)
            vist[i] = 0;
        fa[rt] = 0, dfs(rt);
        std::vector<int> mk;
        for (int i = 1; i <= m; ++i)
            if (fa[u[i]] != v[i] && fa[v[i]] != u[i])
                mk.push_back(i);
        if (m == n || m == n + 1) {
            for (int i = 1; i <= m; ++i)
                ans[i] = 0;
            for (int i : mk)
                ans[i] = 1;
            for (int i = 1; i <= m; ++i)
                putchar(ans[i] ? '1' : '0');
            puts("");
            return;
        }
        std::vector<int> all;
        for (int i : mk)
            all.push_back(u[i]), all.push_back(v[i]);
        std::sort(all.begin(), all.end());
        all.resize(std::unique(all.begin(), all.end()) - all.begin());
        if ((int)all.size() == 3)
            continue;
        for (int i = 1; i <= m; ++i)
            ans[i] = 0;
        for (int i : mk)
            ans[i] = 1;
        for (int i = 1; i <= m; ++i)
            putchar(ans[i] ? '1' : '0');
        puts("");
        return;
    }
}

int main() {
    int T;
    read(T);
    while (T--)
        sov();
}