// Problem: C - K Derangement
// Contest: AtCoder - AtCoder Regular Contest 144
// URL: https://atcoder.jp/contests/arc144/tasks/arc144_c
// Memory Limit: 1024 MB
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
const int maxn = 3e5 + 19;
int n, k;
bool vist[maxn];
void out(const char *usle, int v) {
    printf("%d ", v);
    vist[v] = 1;
}
void outrest() {
    for (int i = 1; i <= n; ++i)
        if (!vist[i])
            printf("%d ", i);
}
int main() {
    read(n), read(k);
    if (k * 2 > n)
        return puts("-1"), 0;
    int p = n / (k + k);
    for (int i = 1; i < p; ++i) {
        for (int j = k + 1; j <= k + k; ++j)
            out("%d ", k * 2 * (i - 1) + j);
        for (int j = 1; j <= k; ++j)
            out("%d ", k * 2 * (i - 1) + j);
    }
    if (n - (p - 1) * (k + k) <= k * 3) {
        for (int i = (p - 1) * (k + k) + k + 1; i <= n; ++i)
            out("%d ", i);
        for (int i = (p - 1) * (k + k) + 1; i <= (p - 1) * (k + k) + k; ++i)
            out("%d ", i);
    } else {
        int m = n - (p - 1) * (k + k) - k * 3, s = (p - 1) * (k + k);
        for (int i = s + 1; i <= s + k; ++i)
            out("%d ", i + k);
        for (int i = s + k + 1; i <= s + k + m; ++i)
            out("%d ", i - k);
        for (int i = s + k + m + 1; i <= s + k + m + k; ++i)
            out("%d ", i + k);
        outrest();
    }
}

/*





















*/