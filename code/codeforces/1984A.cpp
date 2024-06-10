#include <bits/stdc++.h>

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            std::cin >> a[i];
        }

        if (a[1] == a[n]) {
            std::cout << "NO\n";
            continue;
        }

        std::cout << "YES\n";
        std::string s(n, 'B');
        s[1] = 'R';
        std::cout << s << '\n';
    }
}