#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 4e3 + 19;

int n, fa[maxn], sz[maxn], deg[maxn];
char s[maxn][maxn];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y)
        return;
    fa[x] = y, sz[y] += sz[x], sz[x] = 0;
}

std::vector<int> cons;
std::vector<int> con[maxn];

void solve(void) {
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        fa[i] = i, sz[i] = 1, deg[i] = 1;

    for (int i = 1; i <= n; ++i) {
        std::cin >> (s[i] + 1);
        for (int j = 1; j < i; ++j)
            if (s[i][j] == '1')
                merge(i, j);
        for (int j = 1; j <= n; ++j)
            if (s[i][j] == '1')
                ++deg[i];
    }

    cons.clear();
    for (int i = 1; i <= n; ++i)
        con[i].clear();

    for (int i = 1; i <= n; ++i)
        con[find(i)].push_back(i);
    for (int i = 1; i <= n; ++i) {
        assert(con[i].size() == (ll)sz[i]);
        if (con[i].size())
            cons.push_back(i);
    }

    if (cons.size() == 1ll) {
        std::cout << "0\n";
        return;
    }
    for (int i : cons) {
        std::sort(con[i].begin(), con[i].end(),
                  [](const int &x, const int &y) { return deg[x] < deg[y]; });
    }
    for (int i : cons) {
        if (deg[con[i][0]] < sz[i]) {
            std::cout << "1\n" << con[i][0] << '\n';
            return;
        }
    }

    std::sort(cons.begin(), cons.end(),
              [](const int &x, const int &y) { return sz[x] < sz[y]; });
    if (sz[cons[0]] <= 2 || cons.size() < 3) {
        std::cout << sz[cons[0]] << '\n';
        for (int i : con[cons[0]])
            std::cout << i << ' ';
        std::cout << '\n';
    } else {
        std::cout << 2 << '\n';
        std::cout << con[cons[0]][0] << ' ' << con[cons[1]][0] << '\n';
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