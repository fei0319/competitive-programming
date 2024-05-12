#include <bits/stdc++.h>

using ll = long long int;

constexpr int MAXN = 2e2 + 19;

int n, m;
// n == 1 + x + x * y
// x * y = <number of leaves>
// m == n - 1
int deg[MAXN];

void solve(void) {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        deg[i] = 0;
    }
    for (int i = 1; i <= m; ++i) {
        int u, v;
        std::cin >> u >> v;
        ++deg[u], ++deg[v];
    }
    int leaves = 0;
    for (int i = 1; i <= n; ++i) {
        if (deg[i] == 1) {
            ++leaves;
        }
    }
    int x = n - 1 - leaves, y = leaves / x;
    std::cout << x << ' ' << y << '\n';
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