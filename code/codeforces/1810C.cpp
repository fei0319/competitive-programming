#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;
constexpr ll inf = 1e18;

int n, c, d, a[maxn];
int tmp[maxn], tot;

ll tr[maxn], dp[maxn];
void update(int x, ll k) {
    for (; x <= tot; x += x & -x) tr[x] = std::min(tr[x], k);
}
ll query(int x) {
    ll res = inf;
    for (; x; x -= x & -x) res = std::min(res, tr[x]);
    return res;
}

void solve(void) {
    std::cin >> n >> c >> d;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    std::sort(a + 1, a + 1 + n);

    tot = 0;
    for (int i = 1; i <= n; ++i) tmp[++tot] = a[i];
    std::sort(tmp + 1, tmp + 1 + tot);
    tot = std::unique(tmp + 1, tmp + 1 + tot) - tmp - 1;
    for (int i = 1; i <= tot; ++i) tr[i] = dp[i] = inf;

    for (int i = 1; i <= n; ++i) {
        int x = std::lower_bound(tmp + 1, tmp + 1 + tot, a[i]) - tmp;
        update(x, dp[x] = std::min(dp[x], std::min(query(x - 1) - c - d,
                                                   ll(n - 1) * c +
                                                       ll(a[i] - 1) * d -
                                                       (ll)a[i] * d)));
    }

    ll ans = (ll)c * n + d;
    for (int i = 1; i <= tot; ++i)
        ans = std::min(ans, dp[i] + (ll)tmp[i] * d);
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