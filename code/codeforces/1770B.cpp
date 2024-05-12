#include <bits/stdc++.h>

using ll = long long int;

int n, k;

void solve(void) {
    std::cin >> n >> k;
    int l = 1, r = n;
    for (int i = 1; i <= n; ++i) {
        if (i % k == 0)
            std::cout << l++ << ' ';
        else
            std::cout << r-- << ' ';
    }
    std::cout << "\n";
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