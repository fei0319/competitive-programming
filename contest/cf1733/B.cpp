#include <bits/stdc++.h>

void solve() {
    int n, x, y;
    std::cin >> n >> x >> y;

    if (x > y) {
        std::swap(x, y);
    }

    if (x != 0 || y == 0 || (n - 1) % y != 0) {
        std::cout << "-1\n";
        return;
    }

    for (int i = 1; i <= n - 1; i += y)
        for (int j = 1; j <= y; ++j)
            std::cout << i + 1 << " ";
    std::cout << std::endl;
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