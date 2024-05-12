#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;

constexpr int maxn = 2e2 + 19;

int n, m, b;
ull a[maxn][maxn];

void f(int start, int del) {
    for (int i = start; i <= n; i += del)
        for (int j = 1; j <= m; ++j)
            a[i][j] += 1ull << b;
    ++b;
}

void g(int start, int del) {
    for (int j = start; j <= m; j += del)
        for (int i = 1; i <= n; ++i)
            a[i][j] += 1ull << b;
    ++b;
}

void solve(void) {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            a[i][j] = 0;

    b = 0;
    for (int del : {2, 5, 7, 11})
        for (int start = 1; start <= del; ++start)
            f(start, del), g(start, del);

    std::cout << n * m << '\n';
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j)
            std::cout << a[i][j] << ' ';
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