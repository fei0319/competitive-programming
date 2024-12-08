#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 500;

int a[maxn][maxn];

void change(int &x, int &y, char d) {
    if (d == 'R') ++y;
    else if (d == 'L') --y;
    else if (d == 'D') ++x;
    else if (d == 'U') --x;
}

void construct(int n, int pre) {
    int l = 1, r = n * n, p = 0;
    int x = 1, y = 1;
    char d = 'R';
    for (int i = 1; i <= n * n; ++i) {
        //	std::cout << x << ' ' << y << '\n';
        if (p % 2 == 0) a[x][y] = l++;
        else a[x][y] = r--;
        ++p;
        int nx = x, ny = y;
        change(nx, ny, d);
        if (a[nx][ny] || nx > n || ny > n || !nx || !ny) {
            if (d == 'R') d = 'D';
            else if (d == 'D') d = 'L';
            else if (d == 'L') d = 'U';
            else if (d == 'U') d = 'R';
            nx = x, ny = y;
            change(nx, ny, d);
        }
        x = nx, y = ny;
    }
}

void solve(void) {
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) a[i][j] = 0;
    construct(n, 0);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) std::cout << a[i][j] << ' ';
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