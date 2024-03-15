#include <bits/stdc++.h>

using ll = long long int;

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i += k) {
        int len = std::min(k, n - i + 1);
        for (int j = 1, p = i + len / 2; j <= len; ++j) {
            a[p] = i + len - j;
            if (p == i + len - 1) {
                p = i;
            } else {
                p += 1;
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';
    std::cout << (n + k - 1) / k << '\n';

    int cnt = 1;
    for (int i = 1; i <= n; i += k) {
        int len = std::min(k, n - i + 1);
        for (int j = 1; j <= len; ++j) {
            std::cout << cnt << ' ';
        }
        cnt += 1;
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