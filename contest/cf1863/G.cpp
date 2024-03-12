#include <bits/stdc++.h>

using ll = long long int;

const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 19;

int n, a[MAXN];
int deg[MAXN], v[MAXN];

int fa[MAXN];
int getf(int node) {
    return fa[node] == node ? node : fa[node] = getf(fa[node]);
}

std::vector<int> c[MAXN];

int solve(int color) {
    for (int i : c[color]) {
        v[i] = deg[i];
    }

    static int q[MAXN], h, t;
    h = 1, t = 0;
    for (int i : c[color]) {
        if (deg[i] == 0) {
            q[++t] = i;
        }
    }

    while (h <= t) {
        int node = q[h++];
        deg[a[node]] -= 1;
        if (deg[a[node]] == 0) {
            q[++t] = a[node];
        }
    }

    int acyc = 1, cyc = 1;

    for (int i : c[color]) {
        if (deg[i] != 0) {
            cyc = (ll)cyc * (v[i] + 1) % MOD;
        } else {
            acyc = (ll)acyc * (v[i] + 1) % MOD;
        }
    }
    for (int i : c[color]) {
        if (deg[i] != 0) {
            cyc = (cyc - v[i]) % MOD;
        }
    }

    return (ll)cyc * acyc % MOD;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        fa[i] = i;
    }

    for (int i = 1; i <= n; ++i) {
        deg[a[i]] += 1;
        fa[getf(i)] = getf(a[i]);
    }

    for (int i = 1; i <= n; ++i) {
        c[getf(i)].push_back(i);
    }

    int ans = 1;
    for (int i = 1; i <= n; ++i) {
        ans = (ll)ans * solve(i) % MOD;
    }
    ans = (ans + MOD) % MOD;

    std::cout << ans << '\n';

    return 0;
}