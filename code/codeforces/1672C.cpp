// Problem: C. Unequal Array
// Contest: Codeforces - Codeforces Global Round 20
// URL: https://codeforces.com/contest/1672/problem/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) res = res * 10 + ch - 48, ch = getchar();
}

const int maxn = 2e5 + 19;

int n, a[maxn];

int main() {
    int T;
    read(T);
    while (T--) {
        read(n);
        for (int i = 1; i <= n; ++i) read(a[i]);
        int l = n, r = 1;
        for (int i = 1; i < n; ++i)
            if (a[i] == a[i + 1]) {
                l = i;
                break;
            }
        for (int i = n; i > 1; --i)
            if (a[i] == a[i - 1]) {
                r = i;
                break;
            }
        if (l >= r) {
            puts("0");
            continue;
        }
        if (r - l == 1) puts("0");
        else if (r - l == 2)
            puts("1");
        else
            printf("%d\n", r - l - 2);
    }
}