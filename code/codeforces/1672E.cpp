// Problem: E. notepad.exe
// Contest: Codeforces - Codeforces Global Round 20
// URL: https://codeforces.com/contest/1672/problem/E
// Memory Limit: 256 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
typedef long long int ll;
template <typename Tp>
void chkmax(Tp &a, const Tp &b) {
    a = std::max(a, b);
}
template <typename Tp>
void chkmin(Tp &a, const Tp &b) {
    a = std::min(a, b);
}
template <typename Tp>
void read(Tp &res) {
    static char ch;
    ch = getchar(), res = 0;
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) res = res * 10 + ch - 48, ch = getchar();
}

int n;

int check(int w) {
    printf("? %d\n", w), fflush(stdout);
    int h;
    scanf("%d", &h);
    return h ? h : n + 1;
}

int main() {
    read(n);
    int l = 1, r = 1e7;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid) <= 1) r = mid;
        else
            l = mid + 1;
    }
    int w = l, ans = w * check(w), maxh = 1;
    for (int i = 2; i <= n; ++i) {
        w = (ans - 1) / i;
        if (w * maxh > ans) continue;
        int h = check(w);
        chkmax(maxh, h);
        if (h == n + 1) break;
        else if (h <= i)
            ans = w * h, i = h + 1;
    }
    printf("! %d\n", ans);
}