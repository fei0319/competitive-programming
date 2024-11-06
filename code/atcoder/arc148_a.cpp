// Problem: A - mod M
// Contest: AtCoder - AtCoder Regular Contest 148
// URL: https://atcoder.jp/contests/arc148/tasks/arc148_a
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
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

int pabs(int a) { return a > 0 ? a : -a; }
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

const int maxn = 2e5 + 19;

int n, a[maxn];

int main() {
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = n; i >= 2; --i) a[i] = pabs(a[i] - a[i - 1]);
    int x = a[2];
    for (int i = 3; i <= n; ++i) x = gcd(x, a[i]);
    puts(x >= 2 || x == 0 ? "1" : "2");
}