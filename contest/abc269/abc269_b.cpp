// Problem: B - Rectangle Detection
// Contest: AtCoder - UNICORN Programming Contest 2022(AtCoder Beginner Contest
// 269) URL: https://atcoder.jp/contests/abc269/tasks/abc269_b Memory Limit:
// 1024 MB Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
typedef long long int ll;
template <typename Tp> void chkmax(Tp &a, const Tp &b) { a = std::max(a, b); }
template <typename Tp> void chkmin(Tp &a, const Tp &b) { a = std::min(a, b); }
template <typename Tp> void read(Tp &res) {
    static char ch;
    ch = getchar(), res = 0;
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        res = res * 10 + ch - 48, ch = getchar();
}

const int maxn = 1e2 + 19;
char s[maxn][maxn];

int main() {
    int n = 10;
    for (int i = 1; i <= 10; ++i)
        scanf("%s", s[i] + 1);
    int a = 11, b = 0, c = 11, d = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (s[i][j] == '#') {
                chkmin(a, i), chkmax(b, i);
                chkmin(c, j), chkmax(d, j);
            }
    std::cout << a << " " << b << "\n" << c << " " << d;
}