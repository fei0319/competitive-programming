#include <bits/stdc++.h>

template <int m>
struct ModInt {
private:
    int raw_;
    using mint = ModInt;
    using i64 = int64_t;

public:
    ModInt() {
        raw_ = 0;
    }
    template <typename T>
    ModInt(const T &v) {
        raw_ = v % m;
    }
    int value() const {
        return (raw_ + m) % m;
    }
    mint &operator+=(const mint &rhs) {
        raw_ = (raw_ + rhs.raw_) % m;
        return *this;
    }
    mint &operator-=(const mint &rhs) {
        raw_ = (raw_ - rhs.raw_) % m;
        return *this;
    }
    mint &operator*=(const mint &rhs) {
        raw_ = (i64)raw_ * rhs.raw_ % m;
        return *this;
    }
    mint &operator/=(const mint &rhs) {
        raw_ = (i64)raw_ * qpow(rhs.raw_, m - 2) % m;
        return *this;
    }
    friend mint operator+(const mint &lhs, const mint &rhs) {
        return mint(lhs) += rhs;
    }
    friend mint operator-(const mint &lhs, const mint &rhs) {
        return mint(lhs) -= rhs;
    }
    friend mint operator*(const mint &lhs, const mint &rhs) {
        return mint(lhs) *= rhs;
    }
    friend mint operator/(const mint &lhs, const mint &rhs) {
        return mint(lhs) /= rhs;
    }
    static constexpr int mod() {
        return m;
    }
    static constexpr int qpow(int a, int b) {
        int res = 1;
        while (b) {
            if (b & 1) {
                res = (i64)res * a % m;
            }
            a = (i64)a * a % m, b >>= 1;
        }
        return res;
    }
};

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;

constexpr int N = 500, M = 5000;
constexpr int SQRT_M = 72;

mint dp[2][SQRT_M + 1][M + 1][2];
mint s[M + 1];

int main() {
    int t;
    std::cin >> t;

    struct Query {
        int m, id;
    };
    std::vector<std::vector<Query>> query(N + 1);
    for (int i = 0; i < t; ++i) {
        int n, m;
        std::cin >> n >> m;
        query[n].push_back(Query{m, i});
    }

    std::vector<mint> ans(t);

    dp[0][0][0][0] = 1;
    for (int i = 1; i <= N; ++i) {
        const int f = i & 1 ^ 1, g = i & 1;
        memset(dp[g], 0, 2 * (M + 1) * (SQRT_M + 1) * sizeof(mint));
        for (int j = 0; j <= SQRT_M; ++j) {
            for (int k = j * (j - 1) / 2; k + j * (j + 1) / 2 <= M; ++k) {
                const mint v[]{dp[f][j][k][0], dp[f][j][k][1]};

                dp[g][j + 1][k + j][1] += v[0];
                dp[g][j + 1][k + j][0] += v[1];

                dp[g][j][k + j][0] += v[0] * (j * 2);
                dp[g][j][k + j][1] += v[1] * (j * 2);

                dp[g][j][k + j][1] += v[0];
                dp[g][j][k + j][0] += v[1];

                if (j) {
                    dp[g][j - 1][k + j][1] += v[0] * j * (j - 1);
                    dp[g][j - 1][k + j][0] += v[1] * j * (j - 1);

                    dp[g][j - 1][k + j][0] += v[0] * j;
                    dp[g][j - 1][k + j][1] += v[1] * j;
                }
            }
        }

        s[0] = dp[g][0][0][0];
        for (int k = 1; k <= M; ++k) {
            s[k] = s[k - 1] + dp[g][0][k][0];
        }

        for (const auto &q : query[i]) {
            ans[q.id] = s[q.m];
        }
    }

    for (int i = 0; i < t; ++i) {
        std::cout << ans[i].value() << '\n';
    }

    return 0;
}
