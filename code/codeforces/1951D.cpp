#include <bits/stdc++.h>

using ll = long long int;

void solve() {
    ll n, k;
    std::cin >> n >> k;

    if (n > 2 * k - 2) {
        std::cout << "YES\n";
        std::cout << "2\n";
        std::cout << n - k + 1 << ' ' << 1 << '\n';
    } else {
        if (n == k) {
            std::cout << "YES\n";
            std::cout << "1\n1\n";
        } else {
            std::cout << "NO\n";
        }
    }
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