// Problem: A. Two 0-1 sequences
// Contest: Codeforces - CodeTON Round 2 (Div. 1 + Div. 2, Rated, Prizes!)
// URL: https://codeforces.com/contest/1704/problem/A
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

int n, m;
char a[maxn], b[maxn];

int main() {
    int T;
    read(T);
    while (T--) {
        read(n), read(m);
        scanf("%s", a + 1);
        scanf("%s", b + 1);
        bool u = true, v = false;
        for (int i = 2; i <= m; ++i)
            if (b[i] != a[i + n - m])
                u = false;
        for (int i = 1; i <= n - m + 1; ++i)
            if (a[i] == b[1])
                v = true;
        puts(u && v ? "YES" : "NO");
    }
}

/*





















*/