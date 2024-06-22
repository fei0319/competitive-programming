#ifdef ONLINE_JUDGE
#include <bits/stdc++.h>
#endif
#include <cstdint>
#include <iostream>
#include <vector>

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

constexpr int MOD = 998244353;
using mint = ModInt<MOD>;

void solve(std::vector<std::vector<mint>> &b) {
    int n, m, k;
    std::cin >> n >> m >> k;

    for (int i = b.size(); i <= k; ++i) {
        std::vector<mint> f(i + 1);
        for (int j = 1; j < i; ++j) {
            f[j] = b[i - 1][j - 1] + b[i - 1][j] * j;
        }
        f[i] = b[i - 1][i - 1];
        b.push_back(std::move(f));
    }

    const mint p = (m + 1) / 2, q = m / 2;

    mint pt = 1, nt = 1, mt = mint::qpow(m, n);
    const mint m_inv = mint{1} / m;

    mint ans = 0;
    for (int t = 0; t <= k && t <= n; ++t) {
        ans += b[k][t] * pt * nt * mt;
        pt *= p;
        nt *= n - t;
        mt *= m_inv;
    }

    std::cout << ans.value() << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    std::vector<std::vector<mint>> b{{1}};
    while (t--) {
        solve(b);
    }

    return 0;
}