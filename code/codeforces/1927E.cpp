#include <bits/stdc++.h>

using ll = long long int;

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> a(n + 1);
    int l = 0, r = n + 1;
    for (int i = 1; i <= k; ++i) {
        for (int j = i; j <= n; j += k) {
            if (i & 1) {
                a[j] = ++l;
            } else {
                a[j] = --r;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';
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