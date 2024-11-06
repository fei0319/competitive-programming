#include <bits/stdc++.h>
template <int m>
struct ModInt {
private:
    int raw_;
    using mint = ModInt;
    using i64 = int64_t;

public:
    ModInt() { raw_ = 0; }
    template <typename T>
    ModInt(const T &v) {
        raw_ = v % m;
    }
    int value() const { return (raw_ + m) % m; }
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
    static constexpr int mod() { return m; }
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
using i64 = int64_t;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::string s;
    std::cin >> s;
    s = 'P' + s + 'S';

    std::vector<i64> b(n + 2);
    for (int i = 1; i <= n; ++i) {
        std::cin >> b[i];
    }

    auto match = [](char c, char t) { return c == '?' || c == t; };

    std::unordered_set<i64> sum;
    for (int i = 0; i <= n; ++i) {
        if (match(s[i], 'P') && match(s[i + 1], 'S')) {
            sum.insert(b[i] + b[i + 1]);
        }
    }

    mint ans = 0;
    for (const i64 &sum : sum) {
        std::array<mint, 2> f{1, 0};
        for (int i = 1; i <= n + 1; ++i) {
            std::array<mint, 2> nf;
            if (match(s[i], 'P')) {
                // PP
                if (llabs(b[i] - b[i - 1]) <= m) {
                    nf[0] += f[0];
                }
                // SP
                if (llabs(b[i] + b[i - 1] - sum) <= m * 2) {
                    nf[0] += f[1];
                }
            }
            if (match(s[i], 'S')) {
                // PS
                if (b[i - 1] + b[i] == sum) {
                    nf[1] += f[0];
                }
                // SS
                if (llabs(b[i - 1] - b[i]) <= m) {
                    nf[1] += f[1];
                }
            }
            f = nf;
        }
        ans += f[1];
    }

    std::cout << ans.value() << '\n';
}

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}