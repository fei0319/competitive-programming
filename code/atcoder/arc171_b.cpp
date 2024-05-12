#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 2e5 + 19, MOD = 998244353;

int n, a[MAXN], cnt[MAXN];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }

    for (int i = 1; i <= n; ++i) {
        if (a[i] < i || a[a[i]] != a[i]) {
            std::cout << "0\n";
            return 0;
        }
    }

    int prev = 0, ans = 1;
    for (int i = 1; i <= n; ++i) {
        if (cnt[a[i]] == 0) {
            prev += 1;
        }
        cnt[a[i]] += 1;
        if (i == a[i]) {
            ans = (ll)ans * prev % MOD;
            prev -= 1;
        }
    }

    std::cout << ans << '\n';

    return 0;
}