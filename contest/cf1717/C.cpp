// Problem: C. Madoka and Formal Statement
// Contest: Codeforces - Codeforces Round #818 (Div. 2)
// URL: https://codeforces.com/contest/1717/problem/C
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
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        res = res * 10 + ch - 48, ch = getchar();
}

const int maxn = 2e5 + 19;

int n, a[maxn], b[maxn];

int main() {
    int T;
    read(T);
    while (T--) {
        read(n);
        for (int i = 0; i < n; ++i)
            read(a[i]);
        for (int i = 0; i < n; ++i)
            read(b[i]);
        bool ans = true;
        for (int i = 0; i < n; ++i)
            if (a[i] > b[i])
                ans = false;
        for (int i = 0; i < n; ++i)
            if (a[i] <= a[(i + 1) % n] && b[i] > b[(i + 1) % n] + 1)
                ans = false;
        for (int i = 0; i < n; ++i)
            if (a[i] < b[i] && b[i] > b[(i + 1) % n] + 1)
                ans = false;
        puts(ans ? "YES" : "NO");
    }
}