#include <bits/stdc++.h>

using ll = long long int;

void solve(void) {
    std::string s;
    std::cin >> s;
    auto t = s;
    std::reverse(t.begin(), t.end());
    std::cout << s + t << std::endl;
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