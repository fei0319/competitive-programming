// Problem: B. Difference Array
// Contest: Codeforces - Codeforces Round #808 (Div. 1)
// URL: https://codeforces.com/contest/1707/problem/B
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
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        res = res * 10 + ch - 48, ch = getchar();
}

const int maxn = 1e5 + 19;

int n, a[maxn], b[maxn], cnt, tmp;
int za, zb;

void solve() {
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    cnt = n, za = 0;
    while (cnt > 1) {
        zb = 0;
        tmp = 0;
        if (za) {
            if (a[1] != 0)
                b[++tmp] = a[1];
            else
                ++zb;
            zb += za - 1;
        }
        for (int i = 2; i <= cnt; ++i)
            if (a[i] - a[i - 1] != 0)
                b[++tmp] = a[i] - a[i - 1];
            else
                ++zb;
        std::sort(b + 1, b + 1 + tmp);
        cnt = tmp;
        for (int i = 1; i <= cnt; ++i)
            a[i] = b[i];
        std::swap(za, zb);
    }
    if (cnt)
        printf("%d\n", a[1]);
    else
        puts("0");
}

int main() {
    int T;
    read(T);
    while (T--) {
        solve();
    }
}

/*





















*/