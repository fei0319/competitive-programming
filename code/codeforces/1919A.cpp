#include <bits/stdc++.h>

using ll = long long int;

void solve(void) {
    int a, b;
    std::cin >> a >> b;
    std::cout << ((a + b) % 2 ? "Alice" : "Bob") << '\n';
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}