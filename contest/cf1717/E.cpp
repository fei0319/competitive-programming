// Problem: E. Madoka and The Best University
// Contest: Codeforces - Codeforces Round #818 (Div. 2)
// URL: https://codeforces.com/contest/1717/problem/E
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

const int maxn = 1e5 + 19, mod = 1e9 + 7;

int n, f[maxn];

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

ll lcm(int a, int b) { return (ll)a * b / gcd(a, b); }

std::vector<int> d;
int prime[maxn], cnt, power[maxn], dp[maxn];
void dfs(int val, int k) {
    if (k == cnt) {
        d.push_back(val);
        return;
    }
    dfs(val, k + 1);
    for (int i = 1; i <= power[k + 1]; ++i) {
        val *= prime[k + 1];
        dfs(val, k + 1);
    }
}
int sov(int n) {
    cnt = 0;
    int x = n;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) {
            prime[++cnt] = i, power[cnt] = 0;
            while (n % i == 0) {
                n /= i;
                ++power[cnt];
            }
        }
    if (n > 1)
        prime[++cnt] = n, power[cnt] = 1;
    d.clear(), dfs(1, 0);
    std::sort(d.begin(), d.end());
    for (int i = d.size() - 1; i >= 0; --i) {
        dp[i] = x / d[i] - 1;
        for (int j = i + 1; j < (int)d.size(); ++j)
            if (d[j] % d[i] == 0)
                dp[i] -= dp[j];
    }
    return dp[0];
}

int main() {
    read(n);
    for (int i = 2; i <= n; ++i)
        f[i] = sov(i);
    int ans = 0;
    for (int i = 1; i < n; ++i)
        for (int j = i; j < n; j += i)
            ans = (ans + lcm(n - j, i) % mod * f[j / i]) % mod;
    printf("%d\n", ans);
}