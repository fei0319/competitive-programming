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

using i64 = int64_t;
using mint = ModInt<998244353>;
namespace ranges = std::ranges;
constexpr int SIGMA = 26;

void solve() {
    std::array<int, SIGMA> c{};
    for (int &i : c) std::cin >> i;

    const int n = std::accumulate(c.begin(), c.end(), int{});

    std::vector<mint> fact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i;
    std::vector<mint> ifact(n + 1);
    ifact[n] = 1 / fact[n];
    for (int i = n - 1; i >= 0; --i) ifact[i] = ifact[i + 1] * (i + 1);

    mint base = fact[n / 2] * fact[(n + 1) / 2];
    for (int i : c) base *= ifact[i];

    std::vector<mint> dp(n + 1);
    dp[0] = 1;
    for (int x : c) {
        if (!x) continue;
        for (int i = n; i >= x; --i) {
            dp[i] += dp[i - x];
        }
    }
    const mint ans = base * dp[n / 2];
    std::cout << ans() << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) solve();
}
