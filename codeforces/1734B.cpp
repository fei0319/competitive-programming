#include <bits/stdc++.h>

using ll = long long int;

int n;

void solve(void) {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j)
            std::cout << (j == 1 || j == i ? 1 : 0) << ' ';
        std::cout << std::endl;
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