#include <bits/stdc++.h>

auto solve() -> void {
    int n, m;
    std::cin >> n >> m;

    std::string s;
    std::cin >> s;

    std::set<int> black;
    for (int i = 0; i < m; ++i) {
        int x;
        std::cin >> x;
        black.insert(x);
    }

    int x = 1, j = 0;
    for (char c : s) {
        ++x;
        if (c == 'B') {
            while (black.contains(x)) ++x;
        }

        black.insert(x);
        if (c == 'B') {
            while (black.contains(x)) ++x;
        }
    }

    std::cout << black.size() << '\n';
    for (int x : black) std::cout << x << ' ';
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    for (auto _ : std::views::iota(0, t)) solve();
}
