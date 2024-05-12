#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 5e5 + 19, MOD = 998244353;

int n, C;
int L[MAXN], R[MAXN], v[MAXN];
int a[MAXN], tot;

void dfs(int node) {
    if (node == -1)
        return;
    dfs(L[node]);
    a[++tot] = v[node];
    dfs(R[node]);
}

constexpr int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1)
            res = (ll)res * a % MOD;
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}

int binom(int a, int b) {
    int u = 1, d = 1;
    for (int i = a; i > a - b; --i)
        u = (ll)u * i % MOD;
    for (int i = 1; i <= b; ++i)
        d = (ll)d * i % MOD;
    return (ll)u * qpow(d, MOD - 2) % MOD;
}

int f(int l, int r, int x) {
    if (l > r)
        return 0;
    return binom(x + r - l, x);
}

void solve() {
    std::cin >> n >> C;
    for (int i = 1; i <= n; ++i) {
        std::cin >> L[i] >> R[i] >> v[i];
    }

    tot = 0;
    dfs(1);

    a[0] = 1, a[n + 1] = C;
    int ans = 1;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = l;
        if (a[l] != -1) {
            continue;
        }
        while (r + 1 <= n && a[r + 1] == -1) {
            r += 1;
        }
        ans = (ll)ans * f(a[l - 1], a[r + 1], r - l + 1) % MOD;
    }
    std::cout << ans << '\n';
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