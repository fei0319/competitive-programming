#include <bits/stdc++.h>

using ll = long long int;

void solve() {
    int n, a, b;
    std::cin >> n >> a >> b;
    if (n < a) {
        std::cout << "No\n";
        return;
    }
    int t = (n - a) * (n - a);
    if ((n - a) * 2 - 1 <= n) {
        t = (n - a) * (n - a);
    } else {
        t = (n + 1) / 2 * (n - a);
    }

    if (t >= b) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
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