#include <bits/stdc++.h>

using ll = long long int;

void solve(void) {
    int n, m;
    std::cin >> n >> m;
    std::cout << std::max(n, m) << '\n';
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