#include <bits/stdc++.h>

using ll = long long int;

void solve() {
    int n;
    std::cin >> n;
    int l = 0, r = n + 1;
    for (int i = 1; i <= n; ++i) {
        if (i & 1)
            std::cout << ++l;
        else
            std::cout << --r;
        std::cout << ' ';
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