#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e2 + 19;

int n;
char b[maxn][maxn];
std::vector<int> s[maxn];

void solve(void) {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> (b[i] + 1);
        s[i].clear();
    }
    for (int i = 1; i <= n; ++i) {
        s[i].push_back(i);
        for (int j = 1; j <= n; ++j)
            if (b[i][j] == '1')
                s[j].push_back(i);
    }
    for (int i = 1; i <= n; ++i) {
        std::cout << s[i].size() << ' ';
        for (int j : s[i])
            std::cout << j << ' ';
        std::cout << '\n';
    }
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