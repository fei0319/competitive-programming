#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

using ll = long long int;
constexpr int MAXN = 3e5 + 19;

int n;
ll s[MAXN], min[MAXN];

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%lld", s + i), s[i] += s[i - 1];

    min[n] = s[n];
    for (int i = n - 1; i >= 0; --i) min[i] = std::min(s[i], min[i + 1]);

    ll d = 0, ans = 0;
    for (int i = 0; i <= n; ++i)
        if (s[i] - min[i] > d) {
            d = s[i] - min[i];
            ans = s[i];
        }
    printf("%lld\n", ans);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
}