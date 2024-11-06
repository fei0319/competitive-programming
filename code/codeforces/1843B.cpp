#include <cstdio>

using ll = long long int;
constexpr int MAXN = 2e5 + 19;

int n, a[MAXN];

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    ll ans(0);
    int cnt(0);
    for (int l = 1, r; l <= n; l = r + 1) {
        r = l;
        if (a[l] >= 0) {
            ans += a[l];
            continue;
        } else ans -= a[l], ++cnt;
        while (r + 1 <= n && a[r + 1] <= 0) ans -= a[++r];
    }
    printf("%lld %lld\n", ans, cnt);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) solve();
}