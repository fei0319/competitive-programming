// Problem: A. Mark the Photographer
// Contest: Codeforces - Codeforces Round #807 (Div. 2)
// URL: https://codeforces.com/contest/1705/problem/0
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

int T;
int n, x, h[100009];

void solve() {
    read(n), read(x);
    for (int i = 1; i <= n + n; ++i)
        read(h[i]);
    std::sort(h + 1, h + 1 + n + n);
    for (int i = 1; i <= n; ++i)
        if (h[i + n] < h[i] + x) {
            puts("NO");
            return;
        }
    puts("YES");
}

int main() {
    read(T);
    while (T--)
        solve();
}

/*





















*/