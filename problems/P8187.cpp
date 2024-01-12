// Problem: P8187 [USACO22FEB]  Robot Instructions S
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8187
// Memory Limit: 512 MB
// Time Limit: 4000 ms
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

const int maxn = 59;

std::pair<ll, ll> a[1 << 20], b[1 << 20], c[1 << 20];
int n, m, lg2[1 << 20], x[maxn], y[maxn], X, Y, tot[1 << 20][21], pop[1 << 20];
ll ans[maxn];

int main() {
    read(n);
    scanf("%d%d", &X, &Y);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", x + i, y + i);
    m = n / 2, n = n - m;
    for (int i = 2; i < (1 << n); i <<= 1)
        lg2[i] = lg2[i >> 1] + 1;
    for (int i = 1; i < (1 << n); ++i)
        pop[i] = pop[i ^ (i & -i)] + 1;
    for (int i = 1; i < (1 << n); ++i) {
        int j = i & -i;
        a[i] = a[i ^ j];
        a[i].first += x[lg2[j] + 1];
        a[i].second += y[lg2[j] + 1];
    }
    for (int i = 1; i < (1 << m); ++i) {
        int j = i & -i;
        b[i] = b[i ^ j];
        b[i].first += x[lg2[j] + 1 + n];
        b[i].second += y[lg2[j] + 1 + n];
    }
    std::copy(b, b + (1 << m), c);
    std::sort(c, c + (1 << m));
    int cnt = std::unique(c, c + (1 << m)) - c;
    for (int i = 0; i < (1 << n); ++i) {
        ll dx = X - a[i].first, dy = Y - a[i].second;
        int p = std::lower_bound(c, c + cnt, std::make_pair(dx, dy)) - c;
        if (p != cnt && c[p] == std::make_pair(dx, dy))
            ++tot[p][pop[i]];
    }
    for (int i = 0; i < (1 << m); ++i) {
        int p = std::lower_bound(c, c + cnt, b[i]) - c;
        for (int j = 0; j <= n; ++j)
            ans[pop[i] + j] += tot[p][j];
    }
    for (int i = 1; i <= n + m; ++i)
        printf("%lld\n", ans[i]);
}