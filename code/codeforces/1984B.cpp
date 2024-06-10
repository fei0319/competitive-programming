#include <bits/stdc++.h>

void solve() {
    std::string s;
    std::cin >> s;

    int x = 0;
    while (x < s.size() && s[x] != '0') {
        ++x;
    }

    if (s.front() != '1' || s.back() == '9' || (x < s.size() - 1)) {
        std::cout << "NO\n";
    } else {
        std::cout << "YES\n";
    }
}

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
}