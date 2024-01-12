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
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        res = res * 10 + ch - 48, ch = getchar();
}

const int maxn = 1e5 + 19;

int n, p[maxn], dfn[maxn], ind, dep[maxn];
std::vector<int> G[maxn];

void dfs(int node) {
    std::sort(G[node].begin(), G[node].end());
    for (int to : G[node])
        dep[to] = dep[node] + 1, dfs(to);
    dfn[node] = ++ind;
}

int main() {
    read(n);
    for (int i = 1; i <= n; ++i)
        read(p[i]), G[p[i] + 1].emplace_back(i);
    dfs(n + 1);
    printf("%d\n", n + 2);
    for (int i = 1; i <= n; ++i)
        printf("%lld\n", dfn[i] + (ll)(n - dep[i]) * (n + 2));
}