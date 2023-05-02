// Problem: P7529 [USACO21OPEN] Permutation G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7529
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

const int maxn = 42, mod = 1e9 + 7;

int n, x[maxn], y[maxn];
int dp[maxn][maxn][maxn], cnt[maxn][maxn][maxn];

bool cross(int a, int b) { return (ll)x[a] * y[b] - (ll)x[b] * y[a] > 0; }
bool check(int a, int b, int c, int t) {
    bool ab = (ll)(x[a] - x[b]) * (y[t] - y[b]) -
                  (ll)(x[t] - x[b]) * (y[a] - y[b]) >
              0,
         bc = (ll)(x[b] - x[c]) * (y[t] - y[c]) -
                  (ll)(x[t] - x[c]) * (y[b] - y[c]) >
              0,
         ca = (ll)(x[c] - x[a]) * (y[t] - y[a]) -
                  (ll)(x[t] - x[a]) * (y[c] - y[a]) >
              0;
    return ab == bc && bc == ca;
}

std::vector<std::pair<int, std::tuple<int, int, int>>> mk;

int fact[maxn], ifact[maxn];
int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1)
            res = (ll)res * a % mod;
        a = (ll)a * a % mod, b >>= 1;
    }
    return res;
}
void init(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; ++i)
        fact[i] = (ll)fact[i - 1] * i % mod;
    ifact[n] = qpow(fact[n], mod - 2);
    for (int i = n - 1; i >= 0; --i)
        ifact[i] = (ll)ifact[i + 1] * (i + 1) % mod;
}
int A(int n, int m) { return (ll)fact[n] * ifact[n - m] % mod; }

void transfer(int a, int b, int c, int x, int y, int z) {
    if (x > y)
        std::swap(x, y);
    if (y > z)
        std::swap(y, z);
    if (x > y)
        std::swap(x, y);
    dp[a][b][c] =
        (dp[a][b][c] + (ll)dp[x][y][z] * A(n - cnt[x][y][z] - 4,
                                           cnt[a][b][c] - cnt[x][y][z] - 1)) %
        mod;
}

int main() {
    read(n), init(n);
    for (int i = 1; i <= n; ++i)
        read(x[i]), read(y[i]);
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            for (int k = j + 1; k <= n; ++k) {
                for (int p = 1; p <= n; ++p)
                    if (p != i && p != j && p != k && check(i, j, k, p))
                        ++cnt[i][j][k];
                mk.push_back({cnt[i][j][k], {i, j, k}});
            }
    std::sort(mk.begin(), mk.end());
    if (mk.back().first + 3 != n) {
        puts("0");
        return 0;
    }
    for (auto node : mk) {
        auto [x, y, z] = node.second;
        dp[x][y][z] = (ll)A(n - 3, cnt[x][y][z]) * fact[3] % mod;
        for (int i = 1; i <= n; ++i)
            if (i != x && i != y && i != z && check(x, y, z, i)) {
                transfer(x, y, z, i, x, y);
                transfer(x, y, z, i, y, z);
                transfer(x, y, z, i, x, z);
            }
    }
    int ans = 0;
    if (mk.back().first + 3 == n) {
        auto [x, y, z] = mk.back().second;
        ans = (ans + dp[x][y][z]) % mod;
    }
    printf("%d\n", ans);
}