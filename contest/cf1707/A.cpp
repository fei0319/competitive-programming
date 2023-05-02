// Problem: A. Doremy's IQ
// Contest: Codeforces - Codeforces Round #808 (Div. 1)
// URL: https://codeforces.com/contest/1707/problem/A
// Memory Limit: 256 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

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

const int maxn = 1e5 + 19;

int n, q, a[maxn];

bool check(int m) {
    int v = q, end = 0;
    for (int i = 1; i <= n; ++i)
        if (i >= m && a[i] > v)
            --v, end = i;
    if (v >= 1)
        return true;
    if (v < 0)
        return false;
    return end == n;
}

void out(int x) {
    for (int i = 1; i < x; ++i)
        putchar(a[i] <= q ? '1' : '0');
    for (int i = x; i <= n; ++i)
        if (q) {
            putchar('1');
            if (a[i] > q)
                --q;
        } else
            putchar('0');
    puts("");
}

void solve(void) {
    read(n), read(q);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    int l = 1, r = n + 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid;
        else
            l = mid + 1;
    }
    out(l);
}

int main() {
    int T;
    read(T);
    while (T--)
        solve();
}

/*





















*/