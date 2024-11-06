#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

int n, a[maxn], fa[maxn], to[maxn], deg[maxn], sz[maxn], son[maxn];
bool ok[maxn];

int getf(int node) {
    return fa[node] == node ? node : fa[node] = getf(fa[node]);
}

void merge(int x, int y) {
    x = getf(x), y = getf(y);
    if (x != y) fa[x] = y, sz[y] += sz[x];
}

void solve(void) {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];

    for (int i = 1; i <= n; ++i) {
        son[i] = 1;
        ok[i] = 1;
        fa[i] = i;
        sz[i] = 1;
        deg[i] = 0;
        to[i] = i + a[i];
    }

    for (int i = 1; i <= n; ++i) {
        if (to[i] >= 1 && to[i] <= n) ++deg[to[i]], merge(i, to[i]);
    }

    for (int i = 1; i <= n; ++i)
        if (to[i] < 1 || to[i] > n) ok[getf(i)] = 0;

    int oksz = 0;
    for (int i = 1; i <= n; ++i)
        if (getf(i) == i && ok[i]) oksz += sz[i];

    ll ans = 0ll;
    if (ok[getf(1)]) {
        int now = 1;
        while (now >= 1 && now <= n) {
            if (son[now] == 0) break;
            ans += oksz;
            son[now] = 0;
            now = to[now];
        }
        for (int i = 1; i <= n; ++i)
            if (son[i]) ans += n + n + 1;
    } else {
        static int q[maxn], h, t;
        h = 1, t = 0;
        for (int i = 1; i <= n; ++i)
            if (getf(i) == getf(1) && deg[i] == 0) q[++t] = i;
        while (h <= t) {
            int node = q[h++];
            if (to[node] >= 1 && to[node] <= n) {
                --deg[to[node]];
                son[to[node]] += son[node];
                if (deg[to[node]] == 0) q[++t] = to[node];
            }
        }
        int now = 1;
        while (now >= 1 && now <= n) {
            ans += son[now] + oksz;
            now = to[now];
        }
    }

    //	std::cout << ans << '\n';
    std::cout << (ll)n * (n + n + 1) - ans << '\n';
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