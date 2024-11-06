// Problem: P8485 Water
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8485
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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

const int maxn = 5e3 + 19, maxs = 1.6e7 + 19, mod = 998244353;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = (ll)res * a % mod;
        a = (ll)a * a % mod, b >>= 1;
    }
    return res;
}

void iso(auto &a) {
    std::sort(a.begin(), a.end());
    a.resize(std::unique(a.begin(), a.end()) - a.begin());
    a.shrink_to_fit();
}

struct Edge {
    int to, next;
} edge[maxs];
int head[maxs];
inline void add(int from, int to) {
    static int it;
    edge[++it].next = head[from];
    edge[it].to = to;
    head[from] = it;
}

int n, m;
std::vector<bool> map[maxn];
int bel[2][maxn];
int dp[maxs], f[maxn], M[maxn], mul[maxn];
bool chu[maxs];

int fa[maxs];
int getf(int x) { return fa[x] == x ? x : fa[x] = getf(fa[x]); }

int lim;
void dfs(int node, int dep) {
    dp[node] = 1;
    if (dep > lim) lim = dep;
    for (int i = head[node]; i; i = edge[i].next) {
        int to = edge[i].to;
        dfs(to, dep + 1);
        dp[node] = (ll)dp[node] * dp[to] % mod;
    }
    ++dp[node];
    if (!M[dep]) M[dep] = 1;
    M[dep] = (ll)M[dep] * dp[node] % mod;
}

int cnt;
int new_node(void) { return ++cnt; }

int main() {
    read(n), read(m);
    for (int i = 1; i <= n; ++i) {
        static char s[maxn];
        std::scanf("%s", s + 1);
        map[i].resize(m + 1);
        for (int j = 1; j <= m; ++j) map[i][j] = (s[j] == '.');
    }
    for (int i = 1; i <= n; ++i) {
        for (int l = 1, r; l <= m; l = r + 1) {
            r = l;
            if (map[i][l]) {
                while (r + 1 <= m && map[i][r + 1]) ++r;
                bool ok = true;
                for (int j = l; j <= r; ++j)
                    if ((i > 1 && map[i - 1][j]) ||
                        (i < n && map[i + 1][j])) {
                        ok = false;
                        break;
                    }
                if (!ok) continue;
                for (int j = l; j <= r; ++j) map[i][j] = 0;
            }
        }
    }
    /*
    for(int i = 1; i <= n; ++i){
            for(int j = 1; j <= m; ++j)
                    putchar(map[i][j] ? '.' : '#');
            puts("");
    }*/

    for (int i = n; i >= 1; --i) {
        for (int j = 1; j <= m; ++j) bel[i & 1][j] = 0;
        int first = cnt;
        for (int l = 1, r; l <= m; l = r + 1) {
            r = l;
            if (map[i][l]) {
                while (r + 1 <= m && map[i][r + 1]) ++r;
                int cur = new_node();
                fa[cur] = cur, dp[cur] = 1;
                for (int j = l; j <= r; ++j) bel[i & 1][j] = cur;
                for (int j = l; j <= r; ++j)
                    if (i + 1 <= n && map[i + 1][j]) {
                        if (getf(bel[(i + 1) & 1][j]) ==
                            getf(bel[i & 1][j]))
                            continue;
                        if (getf(bel[(i + 1) & 1][j]) > first) {
                            fa[getf(bel[i & 1][j])] =
                                getf(bel[(i + 1) & 1][j]);
                        } else
                            fa[getf(bel[(i + 1) & 1][j])] =
                                getf(bel[i & 1][j]);
                    }
            }
        }
        for (int j = 1; j <= m; ++j) bel[i & 1][j] = getf(bel[i & 1][j]);
        for (int j = 1; j <= m; ++j) {
            int u = bel[i & 1][j], v = bel[(i + 1) & 1][j];
            if (u && v && !chu[v]) add(u, v), chu[v] = true;
        }
    }

    std::vector<int> root;
    for (int i = 1; i <= cnt; ++i)
        if (getf(i) == i) root.emplace_back(i);

    for (int i = 0; i <= n; ++i) f[i] = 1, mul[i] = 1;

    int ans = 0;
    for (int rt : root) {
        lim = 0;
        dfs(rt, 0);
        for (int i = 0; i < lim; ++i)
            f[i] = (ll)f[i] * (M[0] - M[i + 1] + 1) % mod;
        mul[lim] = (ll)mul[lim] * M[0] % mod;
        for (int i = 0; i <= lim; ++i) M[i] = 0;
    }

    for (int i = 1; i <= n; ++i) {
        mul[i] = (ll)mul[i] * mul[i - 1] % mod;
        f[i] = (ll)f[i] * mul[i] % mod;
        ans = (ans + ll(f[i] - f[i - 1]) * i) % mod;
    }
    // printf("%d\n", ans);
    ans = (ll)ans * qpow(f[n], mod - 2) % mod;
    ans = (ans + mod) % mod;
    printf("%d\n", ans);

    // for(int i = 1; i <= n; ++i){
    // for(int j = 1; j <= m; ++j) printf("%2d ", bel[i][j]);
    // puts("");
    // }
}