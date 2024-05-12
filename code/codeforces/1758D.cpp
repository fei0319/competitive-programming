#include <bits/stdc++.h>

using ll = long long int;

int n;

void solve(void) {
    std::cin >> n;
    if (n % 2 == 0) {
        for (int i = 1; i <= n / 2; ++i)
            std::cout << n - i << ' ' << n + i << ' ';
        std::cout << '\n';
    } else {
        std::cout << 3 * n << ' ' << 5 * n << ' ' << 4 * n << ' ';
        for (int i = 1; i <= (n - 3) / 2; ++i)
            std::cout << 4 * n - i << ' ' << 4 * n + i << ' ';
        std::cout << '\n';
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