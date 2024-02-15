#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 1e5 + 19, MAXS = 1 << 20, B = 20;

int n, k, dp[MAXS];
std::vector<int> G[MAXN];

bool vist[MAXS];
int dep[MAXN], fa[MAXN][B];
int s[MAXN], d[MAXN];

void dfs1(int node, int f) {
    dep[node] = dep[f] + 1;
    fa[node][0] = f;
    for (int i = 1; i < B; ++i) {
        fa[node][i] = fa[fa[node][i - 1]][i - 1];
    }

    for (int to : G[node]) {
        if (to == f) continue;
        dfs1(to, node);
    }
}

void dfs2(int node, int f) {
    for (int to : G[node]) {
        if (to == f) continue;
        dfs2(to, node);
        s[node] |= s[to];
    }
    s[node] ^= d[node];
    vist[s[node]] = true;
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) std::swap(x, y);
    for (int i = B - 1; i >= 0; --i) {
        if (dep[fa[x][i]] >= dep[y]) {
            x = fa[x][i];
        }
    }
    if (x == y) return x;
    for (int i = B - 1; i >= 0; --i) {
        if (fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}

void solve() {
    std::cin >> n;

    for (int i = 1; i <= n; ++i) {
        G[i].clear();
        s[i] = 0;
        d[i] = 0;
    }

    for (int i = 2; i <= n; ++i) {
        int u, v;
        std::cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs1(1, 0);

    std::cin >> k;
    for (int i = 0; i < (1 << k); ++i) {
        vist[i] = false;
        dp[i] = k;
    }
    for (int i = 0; i < k; ++i) {
        int a, b;
        std::cin >> a >> b;
        s[a] ^= (1 << i);
        s[b] ^= (1 << i);
        d[lca(a, b)] ^= (1 << i);
    }

    dfs2(1, 0);

    std::vector<int> S;
    for (int i = 1; i < (1 << k); ++i) {
        if (vist[i]) {
            S.push_back(i);
        }
    }
    dp[0] = 0;
    for (int i = 0; i < (1 << k); ++i) {
        for (int j : S) {
            dp[i | j] = std::min(dp[i | j], dp[i] + 1);
        }
    }
    std::cout << dp[(1 << k) - 1] << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}