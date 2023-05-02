#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e5 + 19;

int n, a[maxn];

void solve(void) {
    std::cin >> n;
    int min = 2e9;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        min = std::min(min, a[i]);
    }
    std::cout << (a[1] == min ? "Bob" : "Alice") << std::endl;
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