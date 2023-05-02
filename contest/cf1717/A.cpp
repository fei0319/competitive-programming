// Problem: A. Madoka and Strange Thoughts
// Contest: Codeforces - Codeforces Round #818 (Div. 2)
// URL: https://codeforces.com/contest/1717/problem/A
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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

int main() {
    int T;
    read(T);
    while (T--) {
        int n;
        read(n);
        printf("%d\n", n / 3 * 2 + n / 2 * 2 + n);
    }
}