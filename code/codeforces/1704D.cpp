// Problem: D. Magical Array
// Contest: Codeforces - CodeTON Round 2 (Div. 1 + Div. 2, Rated, Prizes!)
// URL: https://codeforces.com/contest/1704/problem/D
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
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) res = res * 10 + ch - 48, ch = getchar();
}

const int maxn = 1e5 + 19;
int n, m;
ll t[maxn];

int solve() {
    read(n), read(m);
    for (int i = 1; i <= n; ++i) {
        t[i] = 0;
        for (int j = 1; j <= m; ++j) {
            int p;
            read(p);
            t[i] += (ll)p * j;
        }
    }
    for (int i = 2; i < n; ++i)
        if (t[i] != t[i - 1] && t[i] != t[i + 1])
            return printf("%d %lld\n", i, t[i] - t[i - 1]), 0;
    if (t[1] != t[2]) return printf("1 %lld\n", t[1] - t[2]), 0;
    return printf("%d %lld\n", n, t[n] - t[1]), 0;
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