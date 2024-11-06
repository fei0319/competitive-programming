#include <bits/stdc++.h>

using ll = long long int;

void solve(void) {
    int n;
    std::cin >> n;
    int d = 0;
    while (n >= 10) n /= 10, ++d;
    std::cout << n + 9 * d << '\n';
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