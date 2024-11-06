// Problem: D1. Chopping Carrots (Easy Version)
// Contest: Codeforces - Codeforces Round #809 (Div. 2)
// URL: https://codeforces.com/contest/1706/problem/D1
// Memory Limit: 64 MB
// Time Limit: 4000 ms
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
int n, k, a[maxn];

int check(int m) {
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i] < m) return 1e9;
        int v = std::min(a[i] / m, k);
        chkmax(res, a[i] / v - m);
    }
    return res;
}

int main() {
    int T;
    read(T);
    while (T--) {
        read(n), read(k);
        for (int i = 1; i <= n; ++i) read(a[i]);
        int ans = 1e9;
        for (int i = 1; i <= 3000; ++i) chkmin(ans, check(i));
        printf("%d\n", ans);
    }
}

/*





















*/