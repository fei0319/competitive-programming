#include <algorithm>
#include <cstdio>

using ll = long long int;

constexpr int MAXN = 2e5 + 19;

int n, m, q;
std::pair<int, int> p[MAXN];
int x[MAXN];
int a[MAXN];

bool check(int t) {
    for (int i = 1; i <= n; ++i) a[i] = 0;
    for (int i = 1; i <= t; ++i) a[x[i]] = 1;
    for (int i = 1; i <= n; ++i) a[i] += a[i - 1];
    for (int i = 1; i <= m; ++i) {
        int cnt = a[p[i].second] - a[p[i].first - 1];
        if (cnt * 2 > p[i].second - p[i].first + 1) return true;
    }
    return false;
}

void solve() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) scanf("%d%d", &p[i].first, &p[i].second);
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) scanf("%d", x + i);
    int l = 0, r = q;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (!check(mid)) l = mid;
        else r = mid - 1;
    }
    if (l == q) puts("-1");
    else printf("%d\n", l + 1);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) solve();
}