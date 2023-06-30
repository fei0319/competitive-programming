#include <cstdio>

using ll = long long int;

constexpr int MAXN = 1e5 + 19;

int n, m, a[MAXN], b[MAXN];

void solve() {
    scanf("%d%d", &n, &m);
    ll t = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        t += a[i];
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d", b + i);
        t -= b[i];
    }
    if (t > 0) {
        puts("Tsondu");
    } else if (t < 0) {
        puts("Tenzing");
    } else {
        puts("Draw");
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
}