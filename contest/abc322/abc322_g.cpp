#include <algorithm>
#include <iostream>
#include <vector>

using ll = long long int;
const int MOD = 998244353;
const int MAXN = 1e6 + 19;

constexpr ll qpow(ll a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res *= a;
        }
        a *= a, b >>= 1;
    }
    return res;
}

int n, x;
std::vector<int> divisors;

int range_num(int l, int r) {
    if (l <= r) {
        return r - l + 1;
    }
    return 0;
}

int solve1(int S) {
    int S3 = S / 1000, S2 = S / 100 % 10, S1 = S / 10 % 10, S0 = S % 10;
    int max_S = std::max({S3, S2, S1, S0});

    if (S3 == 0) {
        if (S2 == 0) {
            if (S1 != 0 && x % S1 == 0) {
                // a - b = x / S1
                // x / S1 + 1 + max(S_i) <= a <= n
                return range_num(x / S1 + 1 + max_S, n);
            }
            return 0;
        }

        int res = 0;
        for (int d : divisors) {
            int t = x / d - S1;
            if (t % S2 == 0 && (t / S2 - d) % 2 == 0) {
                // 2b + d = t / S2
                int b = (t / S2 - d) / 2, a = b + d;
                if (b >= 1 && a <= n && b > max_S) {
                    res += 1;
                }
            }
        }
        return res;
    } else {
        int res = 0;
        for (int d : divisors) {
            int t = x / d;
            for (int a = max_S + d + 1; S3 * a * a <= t && a <= n; ++a) {
                int b = a - d;
                if (S3 * (a * a + a * b + b * b) + S2 * (a + b) + S1 == t) {
                    res += 1;
                }
            }
        }
        return res;
    }
}

int solve2(int a, int b, int k) {
    int N = (x - (qpow(a, k) - qpow(b, k)));

    static int dp[MAXN];
    std::fill(dp, dp + N + 1, 0);

    dp[0] = 1;
    for (int i = 0; i <= k; ++i) {
        const int L = (i < k) ? std::min(10, b) : (std::min(10, b) - 1);
        int d = qpow(a, i) - qpow(b, i);

        for (int v = N; v >= 0; --v) {
            int res = 0;
            for (int s = 0; s < L && v - s * d >= 0; ++s) {
                res = (res + dp[v - s * d]) % MOD;
            }
            dp[v] = res;
        }
    }
    return dp[N];
}

int main() {
    std::cin >> n >> x;

    for (int i = 1; i <= x; ++i) {
        if (x % i == 0) {
            divisors.push_back(i);
        }
    }

    int ans = 0;

    for (int S = 1; S < 10000; ++S) {
        ans = (ans + solve1(S)) % MOD;
    }
    for (int k = 4; k <= 30; ++k) {
        for (int a = 3; a <= n && qpow(a, k) - qpow(a - 1, k) <= x; ++a)  {
            for (int b = a - 1; b > 1 && qpow(a, k) - qpow(b, k) <= x; --b) {
                ans = (ans + solve2(a, b, k)) % MOD;
            }
        }
    }

    std::cout << ans << '\n';
}