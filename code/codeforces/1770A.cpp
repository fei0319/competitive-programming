#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e5 + 19;

int n, m, a[maxn], b[maxn];

void solve(void) {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int i = 1; i <= m; ++i) std::cin >> b[i];

    ll ans = 0ll;
    std::priority_queue<int, std::vector<int>, std::greater<int>> q;
    for (int i = 1; i <= n; ++i) q.push(a[i]), ans += a[i];
    for (int i = 1; i <= m; ++i) {
        ans -= q.top(), q.pop();
        q.push(b[i]), ans += b[i];
    }
    std::cout << ans << std::endl;
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