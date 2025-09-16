#include <cstdio>

using ll = long long int;

constexpr int MAXN = 1e5 + 19;

int n, x, a[MAXN];

void solve() {
    scanf("%d%d", &n, &x);
    int now = 0;
    for (int _ = 0; _ < 3; ++_) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        for (int i = 1; i <= n; ++i) {
            if ((a[i] | x) == x) now |= a[i];
            else break;
        }
    }
    puts(now == x ? "Yes" : "No");
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
}