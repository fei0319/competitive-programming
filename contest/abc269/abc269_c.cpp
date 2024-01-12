// Problem: C - Submask
// Contest: AtCoder - UNICORN Programming Contest 2022(AtCoder Beginner Contest
// 269) URL: https://atcoder.jp/contests/abc269/tasks/abc269_c Memory Limit:
// 1024 MB Time Limit: 2000 ms
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
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        res = res * 10 + ch - 48, ch = getchar();
}

ll x;
bool b[60];

void dfs(int d, ll v) {
    if (d == -1) {
        printf("%lld\n", v);
        return;
    }
    dfs(d - 1, v);
    if (b[d])
        dfs(d - 1, v + (1ll << d));
}

int main() {
    read(x);
    for (int i = 0; i < 60; ++i)
        if (x & (1ll << i))
            b[i] = 1;
    dfs(59, 0);
}