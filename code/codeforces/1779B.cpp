#include <bits/stdc++.h>

using ll = long long int;

int n;

void solve(void) {
    std::cin >> n;
    if (n == 2) {
        std::cout << "YES\n1 2\n";
        return;
    }
    int a = (n - 2) / 2, b = (n - 1) / 2;
    if (a == 0 || b == 0) {
        std::cout << "NO\n";
        return;
    }
    std::cout << "YES\n";
    for (int i = 1; i <= n; ++i) {
        if (i % 2 == 1) std::cout << a << ' ';
        else std::cout << -b << ' ';
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