#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 4e5 + 19;

int fa[maxn];
int getf(int node) {
    return fa[node] == node ? node : fa[node] = getf(fa[node]);
}

void merge(int x, int y) {
    x = getf(x), y = getf(y);
    fa[x] = y;
}

void solve(void) {
    int n;
    std::cin >> n;
    std::string s[2];
    std::cin >> s[0] >> s[1];
    int c = 0, t = 0;
    for (int i = 0; i < 2 * n; ++i) fa[i] = i;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < n; ++j) {
            if (s[i][j] == 'W') continue;
            int d = 0;
            if (i + 1 < 2 && s[i + 1][j] == 'B')
                ++d, merge(i * n + j, (i + 1) * n + j);
            if (i - 1 >= 0 && s[i - 1][j] == 'B')
                ++d, merge(i * n + j, (i - 1) * n + j);
            if (j + 1 < n && s[i][j + 1] == 'B')
                ++d, merge(i * n + j, i * n + j + 1);
            if (j - 1 >= 0 && s[i][j - 1] == 'B')
                ++d, merge(i * n + j, i * n + j - 1);
            if (d & 1) ++c;
        }
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < n; ++j)
            if (getf(i * n + j) == i * n + j && s[i][j] == 'B') ++t;
    for (int l = 0, r; l < n; l = r + 1) {
        r = l;
        if (s[0][l] == 'W' || s[1][l] == 'W') continue;
        while (r + 1 < n && s[0][r + 1] == 'B' && s[1][r + 1] == 'B') ++r;
        //	std::cout << l << r<< '\n';
        if (l - 1 >= 0 && r + 1 < n) {
            int x = (s[1][l - 1] == 'B'), y = (s[1][r + 1] == 'B');
            if (x != y && (r - l) % 2 == 1) {
                std::cout << "NO\n";
                return;
            } else if (x == y && (r - l) % 2 == 0) {
                std::cout << "NO\n";
                return;
            }
        }
    }
    if (t == 1) std::cout << "YES\n";
    else std::cout << "NO\n";
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