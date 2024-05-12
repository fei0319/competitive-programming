#include <bits/stdc++.h>

using ll = long long int;

int n;

void solve(void) {
    std::cin >> n;
    std::cout << (n + 1) / 2 << std::endl;
    int l = 1, r = n;
    while (l <= r) {
        std::cout << l * 3 - 2 << ' ' << r * 3 - 1 << std::endl;
        ++l, --r;
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