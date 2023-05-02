// Problem: B. Mainak and Interesting Sequence
// Contest: Codeforces Round #819 (Div. 1 + Div. 2) and Grimoire of Code Annual
// Contest 2022 URL: https://codeforces.com/contest/1726/problem/B Memory Limit:
// 256 MB Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
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

int n, m;

void sov() {
    read(n), read(m);
    if (m < n) {
        puts("NO");
        return;
    }
    if (m == n) {
        puts("YES");
        for (int i = 1; i <= n; ++i)
            printf("1 ");
        puts("");
        return;
    }
    if (m == n + 1) {
        if (n & 1) {
            puts("YES");
            for (int i = 1; i < n; ++i)
                printf("1 ");
            printf("2\n");
        } else {
            puts("NO");
        }
        return;
    }
    if (n & 1) {
        puts("YES");
        for (int i = 1; i < n; ++i)
            printf("1 ");
        printf("%d\n", m - n + 1);
    } else {
        if ((m - n + 2) % 2 == 0) {
            puts("YES");
            for (int i = 1; i <= n - 2; ++i)
                printf("1 ");
            printf("%d %d\n", (m - n + 2) / 2, (m - n + 2) / 2);
        } else
            puts("NO");
    }
}

int main() {
    int T;
    read(T);
    while (T--) {
        sov();
    }
}