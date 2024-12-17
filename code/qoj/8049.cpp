#include <bits/stdc++.h>

template <int m>
class ModInt {
    int raw;
    using mint = ModInt;
    using i64 = int64_t;

public:
    ModInt() : raw(0) {}
    ModInt(const auto &v) {
        raw = v % m;
        if (raw < 0) raw += m;
    }
    int operator()() const { return raw; }
    mint &operator+=(const mint &rhs) {
        raw += rhs.raw;
        if (raw >= m) raw -= m;
        return *this;
    }
    mint &operator-=(const mint &rhs) {
        raw -= rhs.raw;
        if (raw < 0) raw += m;
        return *this;
    }
    mint &operator*=(const mint &rhs) {
        raw = (i64)raw * rhs.raw % m;
        return *this;
    }
    mint &operator/=(const mint &rhs) { return *this *= qpow(rhs, m - 2); }

#define DOP(op)                                                           \
    friend mint operator op(const mint &lhs, const mint &rhs) {           \
        return mint{lhs} op## = rhs;                                      \
    }
    DOP(+)
    DOP(-)
    DOP(*)
    DOP(/)
#undef DOP

    static constexpr int mod() { return m; }
    static mint qpow(mint a, i64 b) {
        mint res = 1;
        while (b) {
            if (b & 1) res *= a;
            a *= a, b >>= 1;
        }
        return res;
    }
};

using mint = ModInt<998244353>;
constexpr int MAXN = 502;

mint dp[MAXN][MAXN][MAXN + MAXN];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> lx(n + 1), rx(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> lx[i] >> rx[i];

    std::vector<int> ly(m + 1), ry(m + 1);
    for (int i = 1; i <= m; ++i) std::cin >> ly[i] >> ry[i];

    const int V = std::max(*std::max_element(rx.begin(), rx.end()),
                           *std::max_element(ry.begin(), ry.end()));

    dp[0][0][0 + MAXN] = 1;
    dp[0][0][1 + MAXN] = -1;
    for (int a = 0; a <= n; ++a) {
        for (int b = 0; b <= m; ++b) {
            for (int k = -V; k <= V; ++k) {
                dp[a][b][k + MAXN] += dp[a][b][k + MAXN - 1];
            }
            for (int k = -V; k <= V; ++k) {
                if (k <= 0 && a + 1 <= n) {
                    dp[a + 1][b][k + lx[a + 1] + MAXN] +=
                        dp[a][b][k + MAXN];
                    dp[a + 1][b][k + rx[a + 1] + 1 + MAXN] -=
                        dp[a][b][k + MAXN];
                } else if (k > 0 && b + 1 <= m) {
                    dp[a][b + 1][k - ry[b + 1] + MAXN] +=
                        dp[a][b][k + MAXN];
                    dp[a][b + 1][k - ly[b + 1] + 1 + MAXN] -=
                        dp[a][b][k + MAXN];
                }
            }
        }
    }

    for (int a = 1; a <= n; ++a) {
        for (int b = 1; b <= m; ++b) {
            std::cout << dp[a][b][MAXN]() << ' ';
        }
        std::cout << '\n';
    }
}
