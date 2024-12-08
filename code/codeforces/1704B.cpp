// Problem: B. Luke is a foodie
// Contest: Codeforces - CodeTON Round 2 (Div. 1 + Div. 2, Rated, Prizes!)
// URL: https://codeforces.com/contest/1704/problem/B
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
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) res = res * 10 + ch - 48, ch = getchar();
}

const int maxn = 2e5 + 19;
int n, x, a[maxn];

int main() {
    int T;
    read(T);
    while (T--) {
        read(n), read(x);
        for (int i = 1; i <= n; ++i) read(a[i]);
        int min = 1e9, max = 0, ans = 0;
        for (int i = 1; i <= n; ++i) {
            chkmin(min, a[i]), chkmax(max, a[i]);
            if (max - min > x + x) {
                min = max = a[i], ++ans;
            }
        }
        printf("%d\n", ans);
    }
}

/*





















*/