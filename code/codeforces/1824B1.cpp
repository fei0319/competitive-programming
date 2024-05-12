#include <bits/stdc++.h>

using ll = long long int;
constexpr int maxn = 2e5 + 19, mod = 1e9 + 7;

int n, k, sz[maxn];
std::vector<int> G[maxn];
int ans, tot, nc[maxn];

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = (ll)res * a % mod;
        }
        a = (ll)a * a % mod;
        b >>= 1;
    }
    return res;
}

int fact[maxn], ifact[maxn];
int binom(int n, int m) {
    return (ll)fact[n] * ifact[n - m] % mod * ifact[m] % mod;
}

void ttt(int sz) {
    int res = (ll)binom(sz - 1, k / 2) * binom(n - sz, k - (k / 2 + 1)) % mod;
    printf("%d %d\n", sz, res);
    ans = (ans - (ll)(n - sz) * res) % mod;
}

void dfs(int node, int f) {
    sz[node] = 1;
    for (int to : G[node]) {
        if (to == f)
            continue;
        dfs(to, node);
        sz[node] += sz[to];
        ttt(n - sz[to]);
    }
    ttt(sz[node]);
}

int main() {

    scanf("%d%d", &n, &k);
    fact[0] = 1;
    for (int i = 1; i <= n; ++i)
        fact[i] = (ll)fact[i - 1] * i % mod;
    ifact[n] = qpow(fact[n], mod - 2);
    for (int i = n - 1; i >= 0; --i)
        ifact[i] = (ll)ifact[i + 1] * (i + 1) % mod;

    for (int i = 2; i <= n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v), G[v].push_back(u);
    }
    tot = binom(n, k);

    ans = (ll)n * tot % mod;
    dfs(1, 0);

    ans = (ll)ans * qpow(tot, mod - 2) % mod;
    ans = (ans + mod) % mod;
    printf("%d\n", ans);
}