// Problem: C. Half Queen Cover
// Contest: Codeforces Round #783 (Div. 1)
// URL: https://codeforces.com/contest/1667/problem/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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

int n;

int main() {
    read(n);
    if (n == 1 || n == 2)
        return puts("1\n1 1"), 0;
    int a = (n + 1) / 3;
    printf("%d\n", n - a);
    for (int i = 1; i < a; ++i)
        printf("%d %d\n", a - 1 + i, 2 * a - i), printf("%d %d\n", i, a - i);
    printf("%d %d\n", 2 * a - 1, a);
    for (int i = 3 * a; i <= n; ++i)
        printf("%d %d\n", i, i);
}