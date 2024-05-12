#include <cstdio>

using ll = long long int;

void solve() {
    ll n, ans(0);
    scanf("%lld", &n);
    while (n) {
        ans += n;
        n /= 2;
    }
    printf("%lld\n", ans);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--)
        solve();
}