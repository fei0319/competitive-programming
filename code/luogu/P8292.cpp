// Problem: P8292 [省选联考 2022] 卡牌
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8292
// Memory Limit: 512 MB
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

const int maxn = 300 + 19, maxs = 2e3 + 19, mod = 998244353;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = (ll)res * a % mod;
        a = (ll)a * a % mod, b >>= 1;
    }
    return res;
}

int n, m, p[maxs], res[1 << 13];
int dp[maxn][1 << 13], num[maxn][1 << 13];

int prime[maxs], cnt, kth[maxs], p2[1000009];
bool notprime[maxs];

inline void add(int &a, int b) { a = (a + b) % mod; }
inline void mul(int &a, int b) { a = (ll)a * b % mod; }
inline int rev(int s) { return ((1 << 13) - 1) ^ s; }

int main() {
    for (int i = 2; i <= 2000; ++i) {
        if (!notprime[i]) prime[++cnt] = i, kth[i] = cnt;
        for (int j = 1; j <= cnt && i * prime[j] <= 2000; ++j) {
            notprime[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
    p2[0] = 1;
    for (int i = 1; i < 1000009; ++i) p2[i] = p2[i - 1] * 2 % mod;

    read(n);
    for (int i = 1, s; i <= n; ++i) {
        read(s);
        ++p[s];
    }
    for (int i = 1; i <= 2000; ++i) {
        int x = 0, s = 0;
        for (int j = 1; j <= 13; ++j)
            if (i % prime[j] == 0) s |= 1 << (j - 1);
        for (int j = 14; j <= cnt; ++j)
            if (i % prime[j] == 0) x = j;
        add(num[x][s], p[i]);
    }
    for (int i = 1; i <= 2000; ++i) {
        int x = 0, s = 0;
        for (int j = 1; j <= 13; ++j)
            if (i % prime[j] == 0) s |= 1 << (j - 1);
        for (int j = 14; j <= cnt; ++j)
            if (i % prime[j] == 0) x = j;
        if (!num[x][s]) continue;
        int val = num[x][s], S = rev(s);
        for (int j = S; j; j = (j - 1) & S)
            add(dp[x][rev(j)], val), add(res[rev(j)], val);
        add(dp[x][rev(0)], val), add(res[rev(0)], val);
        num[x][s] = 0;
    }
    for (int i = 14; i <= cnt; ++i)
        for (int s = 0; s < (1 << 13); ++s) {
            int val = p2[dp[i][s]];
            dp[i][s] = ll(val - 1) * qpow(val, mod - 2) % mod;
        }
    for (int s = 0; s < (1 << 13); ++s) {
        // for(int j = 1; j <= 13; ++j)
        // if(s & (1 << (j - 1)))
        // printf("%d ", prime[j]);
        // printf(":\n%d\n", res[s]);
        res[s] = p2[res[s]];
    }
    read(m);
    while (m--) {
        int c;
        read(c);
        std::vector<int> all;
        int s = 0;
        while (c--) {
            int x;
            read(x), x = kth[x];
            if (x <= 13) s ^= 1 << (x - 1);
            else
                all.emplace_back(x);
        }
        std::sort(all.begin(), all.end());
        all.resize(std::unique(all.begin(), all.end()) - all.begin());
        int ans = 0;
        static int tmp[1 << 13];
        for (int i = 0; i < (1 << 13); ++i) tmp[i] = res[i];
        for (int x : all) {
            for (int i = s; i; i = s & (i - 1))
                mul(tmp[i | rev(s)], dp[x][i | rev(s)]);
            mul(tmp[0 | rev(s)], dp[x][0 | rev(s)]);
        }
        for (int i = s; i; i = s & (i - 1))
            add(ans, (__builtin_popcount(s ^ i) & 1 ? -1 : 1) *
                         tmp[i | rev(s)]);
        add(ans,
            (__builtin_popcount(s ^ 0) & 1 ? -1 : 1) * tmp[0 | rev(s)]);
        printf("%d\n", (ans + mod) % mod);
    }
}