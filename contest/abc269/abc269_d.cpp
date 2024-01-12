// Problem: D - Do use hexagon grid
// Contest: AtCoder - UNICORN Programming Contest 2022(AtCoder Beginner Contest
// 269) URL: https://atcoder.jp/contests/abc269/tasks/abc269_d Memory Limit:
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

const int maxn = 1e3 + 19;

int fa[maxn];
int getf(int x) {
    return fa[x] == x ? x : fa[x] = getf(fa[x]);
}
int n, x[maxn], y[maxn];

bool adj(int a, int b) {
    return (x[a] == x[b] - 1 && y[a] == y[b] - 1) ||
           (x[a] == x[b] - 1 && y[a] == y[b]) ||
           (x[a] == x[b] && y[a] == y[b] - 1) ||
           (x[a] == x[b] && y[a] == y[b] + 1) ||
           (x[a] == x[b] + 1 && y[a] == y[b]) ||
           (x[a] == x[b] + 1 && y[a] == y[b] + 1);
}

int main() {
    read(n);
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", x + i, y + i);
        for (int j = 1; j < i; ++j)
            if (adj(i, j)) {
                if (getf(i) != getf(j))
                    fa[getf(i)] = getf(j);
            }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        if (getf(i) == i)
            ++ans;
    std::cout << ans;
}