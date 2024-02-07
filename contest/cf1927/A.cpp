#include <bits/stdc++.h>

using ll = long long int;

void solve() {
    int n;
    std::string s;
    std::cin >> n >> s;

    int l = n, r = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'B') {
            l = std::min(l, i);
            r = std::max(r, i);
        }
    }
    std::cout << r - l + 1 << '\n';
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