// Problem: E - Last Rook
// Contest: AtCoder - UNICORN Programming Contest 2022(AtCoder Beginner Contest
// 269) URL: https://atcoder.jp/contests/abc269/tasks/abc269_e Memory Limit:
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

int n;

int query(int a, int b, int c, int d) {
    printf("? %d %d %d %d\n", a, b, c, d);
    fflush(stdout);
    int res;
    scanf("%d", &res);
    return res;
}

int main() {
    read(n);
    int x, y;
    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (query(l, mid, 1, n) < mid - l + 1)
            r = mid;
        else
            l = mid + 1;
    }
    x = l;
    l = 1, r = n;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (query(1, n, l, mid) < mid - l + 1)
            r = mid;
        else
            l = mid + 1;
    }
    y = l;
    printf("! %d %d\n", x, y);
    fflush(stdout);
}