// Problem: F - Numbered Checker
// Contest: AtCoder - UNICORN Programming Contest 2022(AtCoder Beginner
// Contest 269) URL: https://atcoder.jp/contests/abc269/tasks/abc269_f
// Memory Limit: 1024 MB Time Limit: 3000 ms
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

const int mod = 998244353;
int n, m, q, a, b, c, d;

int sum(int x, int y) {
    --x;
    return ((ll)y * (y + 1) / 2 - (ll)x * (x + 1) / 2) % mod;
}

int Evcount(int l, int r) { return r / 2 - (l - 1) / 2; }
int Evsum(int l, int r) {
    if (l == r) return l % 2 == 0 ? l : 0;
    return sum((l - 1) / 2 + 1, r / 2) * 2 % mod;
}

int main() {
    read(n), read(m), read(q);
    while (q--) {
        read(a), read(b), read(c), read(d);
        int c1 = 0, c2 = 0, sod1 = 0, sod2 = 0, sev1 = 0, sev2 = 0;

        c1 = b - a + 1 - Evcount(a, b);
        sev1 = Evsum(a, b);
        sod1 = (sum(a, b) - sev1) % mod;
        sev1 = ((ll)sev1 * m - ll(b - a + 1 - c1) * m) % mod;
        sod1 = ((ll)sod1 * m - ll(c1) * m) % mod;

        c2 = d - c + 1 - Evcount(c, d);
        sev2 = Evsum(c, d);
        sod2 = (sum(c, d) - sev2) % mod;

        int ans = 0;
        ans = (ans + (ll)sod1 * c2) % mod;
        ans = (ans + (ll)sod2 * c1) % mod;
        ans = (ans + (ll)sev1 * (d - c + 1 - c2)) % mod;
        ans = (ans + (ll)sev2 * (b - a + 1 - c1)) % mod;
        printf("%d\n", (ans + mod) % mod);
    }
}