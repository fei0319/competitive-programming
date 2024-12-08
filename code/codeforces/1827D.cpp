#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 5e5 + 19, B = 20;

std::vector<int> G[MAXN];

int n;
int dfn[MAXN], size[MAXN], tot;
int dep[MAXN], fa[MAXN][B];
void dfs(int node) {
    for (int i = 1; i < B; ++i) {
        fa[node][i] = fa[fa[node][i - 1]][i - 1];
    }

    dfn[node] = ++tot;
    size[node] = 1;
    for (int to : G[node]) {
        fa[to][0] = node;
        dep[to] = dep[node] + 1;
        dfs(to);
        size[node] += size[to];
    }
}

struct BIT {
    int tr[MAXN];
    void update(int x, int k) {
        for (; x <= n; x += x & -x) {
            tr[x] += k;
        }
    }
    int query(int x) {
        int res = 0;
        for (; x; x -= x & -x) {
            res += tr[x];
        }
        return res;
    }
    int query(int l, int r) { return query(r) - query(l - 1); }
} mt;

// Check whether y is in the subtree of x
bool in_subtree(int x, int y) {
    return dfn[y] >= dfn[x] && dfn[y] < dfn[x] + size[x];
}

int son(int f, int x) {
    for (int b = B - 1; b >= 0; --b) {
        if (dep[fa[x][b]] > dep[f]) {
            x = fa[x][b];
        }
    }
    return x;
}

bool check_centroid(int g, int x, int n) {
    if (in_subtree(g, x)) {
        int p = son(g, x);
        return mt.query(dfn[p], dfn[p] + size[p] - 1) <= n / 2;
    } else {
        return n - mt.query(dfn[g], dfn[g] + size[g] - 1) <= n / 2;
    }
}

void solve() {
    std::cin >> n;
    std::for_each(G + 1, G + 1 + n, [](auto &v) { v.clear(); });
    for (int i = 2; i <= n; ++i) {
        int p;
        std::cin >> p;
        G[p].push_back(i);
    }

    tot = 0;
    dfs(1);

    int g = 1, max = 0;
    std::fill(mt.tr + 1, mt.tr + 1 + n, 0);
    for (int i = 2; i <= n; ++i) {
        mt.update(dfn[i], 1);

        if (!check_centroid(g, i, i)) {
            if (in_subtree(g, i)) {
                int x = son(g, i);
                g = x;
                max = 0;
            } else {
                max = mt.query(dfn[g], dfn[g] + size[g] - 1);
                g = fa[g][0];
            }
        } else if (in_subtree(g, i)) {
            int x = son(g, i);
            max = std::max(max, mt.query(dfn[x], dfn[x] + size[x] - 1));
        }

        int res =
            std::max(max, i - mt.query(dfn[g], dfn[g] + size[g] - 1));
        std::cout << i - res * 2 << ' ';
    }
    std::cout << '\n';
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