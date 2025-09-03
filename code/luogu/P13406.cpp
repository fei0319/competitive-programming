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
using mint = ModInt<static_cast<int>(1e9 + 7)>;

void solve() {
    i64 n, b;
    std::cin >> n >> b;

    auto write = [&](auto &self, i64 n) -> std::vector<int> {
        std::vector<int> prefix{};
        if (n >= b) prefix = self(self, n / b);
        prefix.push_back(n % b);
        return prefix;
    };
    auto a = write(write, n);
    std::ranges::reverse(a);

    const int max_k = b;
    const int max_carry = b * (b - 1) / 2 / b;

    std::vector<mint> fact(max_k + 1), ifact(max_k + 1);
    fact[0] = 1;
    for (int i = 1; i <= max_k; ++i) fact[i] = fact[i - 1] * i;
    ifact[max_k] = 1 / fact[max_k];
    for (int i = max_k - 1; i >= 0; --i) ifact[i] = ifact[i + 1] * (i + 1);
    auto binom = [&](int n, int m) -> mint {
        return fact[n] * ifact[n - m] * ifact[m];
    };

    std::vector<std::vector<mint>> dp(max_carry * b + b,
                                      std::vector<mint>(max_k + 1));
    dp[0][0] = 1;
    for (int x = 1; x < b; ++x)
        for (int k = max_k; k >= 1; --k) {
            for (int v = dp.size() - 1; v >= x; --v) {
                dp[v][k] += dp[v - x][k - 1];
            }
        }

    static int mem[80][80][80][2];
    memset(mem, -1, sizeof(mem));
    auto dfs = [&](auto &self, int x, int k, int carry,
                   bool has_zero) -> int {
        int &dest = mem[x][k][carry][has_zero];
        if (dest != -1) return dest;

        if (x == 0) {
            const int v = a[x] + carry * b;
            return dest = dp[v][k - has_zero]();
        }

        mint res{};
        for (int next_k = k; next_k <= max_k; ++next_k) {
            for (int next_carry = 0; next_carry <= max_carry;
                 ++next_carry) {
                const int v = a[x] + carry * b - next_carry;
                if (v < 0) continue;
                for (bool next_has_zero : {true, false}) {
                    const mint comb =
                        binom(next_k - next_has_zero, k - next_has_zero) *
                        fact[k];
                    const mint divd = dp[v][k - has_zero];
                    res += comb * divd *
                           self(self, x - 1, next_k, next_carry,
                                next_has_zero);
                }
            }
        }
        return dest = res();
    };

    mint ans{};
    for (int k = 1; k <= max_k; ++k) {
        ans += dfs(dfs, a.size() - 1, k, 0, false);
        if (a.size() >= 2 && a.back() <= max_carry) {
            ans += dfs(dfs, a.size() - 2, k, a.back(), false);
        }
    }
    std::cout << ans() << '\n';
}

int main() {
    int t;
    std::cin >> t;

    for (int t : std::views::iota(0, t)) {
        std::cout << std::format("Case #{}: ", t + 1);
        solve();
    }
}
