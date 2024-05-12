#include <bits/stdc++.h>

using ll = long long int;
const int MAXN = 2e5 + 19, MOD = 998244353;

constexpr int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1)
            res = (ll)res * a % MOD;
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}

int n, s, t;
int deg[MAXN], fa[MAXN], son[MAXN];
std::vector<int> G[MAXN];

int p[MAXN], v[MAXN];

void dfs0(int node, int f) {
    fa[node] = f;
    for (int to : G[node]) {
        if (to == f)
            continue;
        dfs0(to, node);
    }
}

void dfs1(int node, int f) {
    if (!son[node]) {
        int numerator = (ll)deg[f] * v[f] % MOD;
        int denominator = (ll)deg[node] * (1 + numerator) % MOD;
        v[node] = (ll)numerator * qpow(denominator, MOD - 2) % MOD;
        p[node] = (ll)p[f] * qpow(1 + numerator, MOD - 2) % MOD;
    }

    for (int to : G[node]) {
        if (to == f || to == son[node])
            continue;
        dfs1(to, node);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> s >> t;
    for (int i = 2; i <= n; ++i) {
        int u, v;
        std::cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs0(s, 0);

    G[t] = std::vector<int>{fa[t]};
    for (int i = 1; i <= n; ++i) {
        deg[i] = G[i].size();
    }

    son[t] = -1;
    for (int i = t; i; i = fa[i]) {
        son[fa[i]] = i;

        p[i] = 1;
        if (i == t) {
            v[i] = 1;
        } else if (son[i] == t) {
            v[i] = qpow(deg[i], MOD - 2);
        } else {
            int numerator = (ll)deg[son[i]] * v[son[i]] % MOD;
            int denominator = (ll)deg[i] * (1 + numerator) % MOD;
            v[i] = (ll)numerator * qpow(denominator, MOD - 2) % MOD;
        }

        dfs1(i, fa[i]);
    }

    for (int i = 1; i <= n; ++i) {
        std::cout << ((ll)p[i] * qpow(v[i], MOD - 2) % MOD + MOD) % MOD << ' ';
    }

    return 0;
}