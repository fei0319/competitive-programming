// Problem: C. Mark and His Unfinished Essay
// Contest: Codeforces - Codeforces Round #807 (Div. 2)
// URL: https://codeforces.com/contest/1705/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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

const int maxn = 2e5 + 19;

int n, c, q;
ll l[maxn], r[maxn], len[maxn];
char s[maxn];

void solve(void) {
    read(n), read(c), read(q);
    std::scanf("%s", s + 1);
    len[0] = n;
    for (int i = 1; i <= c; ++i)
        read(l[i]), read(r[i]);
    for (int i = 1; i <= c; ++i)
        len[i] = len[i - 1] + r[i] - l[i] + 1;
    while (q--) {
        ll k;
        read(k);
        for (int i = c; i >= 1; --i)
            if (k > len[i - 1])
                k = k - len[i - 1] + l[i] - 1;
        putchar(s[k]);
        puts("");
    }
}

int main() {
    int T;
    read(T);
    while (T--)
        solve();
}

/*





















*/