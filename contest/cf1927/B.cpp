#include <bits/stdc++.h>

using ll = long long int;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int &i : a) {
        std::cin >> i;
    }

    std::vector<std::vector<char>> b(n + 1);
    for (char c = 'a'; c <= 'z'; ++c) {
        b[0].push_back(c);
    }
    for (int i = 0; i < n; ++i) {
        std::cout << b[a[i]].back();
        b[a[i] + 1].push_back(b[a[i]].back());
        b[a[i]].pop_back();
    }
    std::cout << '\n';
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