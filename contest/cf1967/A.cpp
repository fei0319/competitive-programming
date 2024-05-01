#include <bits/stdc++.h>

using ll = long long int;

void solve() {
    int n;
    ll k;

    std::cin >> n >> k;

    std::vector<ll> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }

    std::sort(a.begin() + 1, a.end());

    ll sum = 0;
    int p = 1;
    for (int i = 1; i <= n; ++i) {
        sum += a[i];
        if (a[i] * i - sum <= k) {
            p = i;
        }
    }

    for (int i = 1; i < p; ++i) {
        k -= a[p] - a[i];
        a[i] = a[p];
    }

    for (int i = 1; i <= p; ++i) {
        a[i] += k / p;
    }
    for (int i = 1; i <= k % p; ++i) {
        a[i] += 1;
    }

    std::sort(a.begin() + 1, a.end());

    if (a[1] == 0) {
        std::cout << "0\n";
        return;
    }

    ll x = a[1], ans = x * n - (n - 1);
    for (int i = 1; i <= n; ++i) {
        if (a[i] > x) {
            ++ans;
        }
    }
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