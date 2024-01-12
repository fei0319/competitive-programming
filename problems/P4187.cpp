// Problem: P4187 [USACO18JAN]Stamp Painting G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4187
// Memory Limit: 125 MB
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

const int maxn = 1e6 + 19, mod = 1e9 + 7;

int n, m, k;
int dp[maxn], cont[maxn], p, sum, ans;

int main() {
    read(n), read(m), read(k);
    dp[0] = 1, cont[0] = m, sum = m;
    for (int i = 1; i <= n; ++i) {
        while (i - p >= k)
            sum = (sum - cont[p++]) % mod;
        dp[i] = sum, cont[i] = (ll)dp[i] * (m - 1) % mod;
        sum = (sum + cont[i]) % mod;
    }
    ans = 1;
    for (int i = 1; i <= n; ++i)
        ans = (ll)ans * m % mod;
    ans = (ans - dp[n]) % mod;
    printf("%d\n", (ans + mod) % mod);
}