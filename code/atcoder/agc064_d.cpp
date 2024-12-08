#include <iostream>

using ll = long long int;
const int MAXN = 309;
const int MOD = 998244353;

int n, m, a[MAXN];
int dp[MAXN][MAXN][MAXN], f[MAXN][MAXN][MAXN];
std::string s;

void add(auto &x, const auto &y) { x = (x + y) % MOD; }

int fact[MAXN], ifact[MAXN];
int binom(int n, int m) {
    return (ll)fact[n] * ifact[n - m] % MOD * ifact[m] % MOD;
}
constexpr int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = (ll)res * a % MOD;
        }
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}
void init(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fact[i] = (ll)fact[i - 1] * i % MOD;
    }
    ifact[n] = qpow(fact[n], MOD - 2);
    for (int i = n - 1; i >= 0; --i) {
        ifact[i] = (ll)ifact[i + 1] * (i + 1) % MOD;
    }
}

int main() {
    std::cin >> n;
    std::cin >> s;

    init(n);

    for (int i = 0, j = 0; i < n; ++i) {
        if (s[i] == 'B') {
            a[++m] = j;
        } else {
            ++j;
        }
    }

    dp[0][0][0] = 1;
    for (int j = 1; j <= a[m]; ++j) {
        for (int k = 0; k <= a[m]; ++k) {
            f[0][j][k] = (f[0][j - 1][k] + dp[0][j - 1][k]) % MOD;
        }
    }
    // i minimum, last one is j, sum is k

    for (int i = 1; i <= m - 1; ++i) {
        dp[i][0][0] = 1;
        for (int j = 1; j <= a[i]; ++j) {
            for (int k = j; k <= a[i]; ++k) {
                for (int p = i - 1; k - (i - p) * j >= 0 && p >= 0 &&
                                    k - (i - p) * j <= a[p];
                     --p) {
                    add(dp[i][j][k],
                        (ll)f[p][j][k - (i - p) * j] * binom(i, p));
                }
            }
        }
        for (int j = 1; j <= a[m]; ++j) {
            for (int k = 0; k <= a[m]; ++k) {
                f[i][j][k] = (f[i][j - 1][k] + dp[i][j - 1][k]) % MOD;
            }
        }
    }

    int ans = 0;
    for (int j = 0; j <= a[m]; ++j) {
        for (int k = 0; k <= a[m]; ++k) {
            add(ans, dp[m - 1][j][k]);
        }
    }
    std::cout << ans << '\n';

    return 0;
}
