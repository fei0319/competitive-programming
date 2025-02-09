#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e5 + 19, mod = 998244353;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = (ll)res * a % mod;
        a = (ll)a * a % mod, b >>= 1;
    }
    return res;
}

int fa[maxn], sz[maxn], dg[maxn];
int getf(int node) {
    return fa[node] == node ? node : fa[node] = getf(fa[node]);
}
void merge(int x, int y) {
    x = getf(x), y = getf(y);
    if (x != y) {
        fa[x] = y;
        sz[y] += sz[x], sz[x] = 0;
        dg[y] += dg[x], dg[x] = 0;
    }
}

int n, a[maxn], b[maxn];

void solve(void) {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int i = 1; i <= n; ++i) std::cin >> b[i];

    int ans = 1, half_n = (ll)n * qpow(2, mod - 2) % mod;
    for (int i = 1; i <= n; ++i) fa[i] = i, sz[i] = 1, dg[i] = 0;
    for (int i = 1; i <= n; ++i) {
        merge(a[i], b[i]);
        ++dg[getf(a[i])];
        if (a[i] == b[i]) ans = (ll)ans * half_n % mod;
    }

    for (int i = 1; i <= n; ++i)
        if (fa[i] == i) {
            if (sz[i] != dg[i]) ans = 0;
            else
                ans = ans * 2 % mod;
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