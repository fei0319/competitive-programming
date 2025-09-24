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

constexpr int N = 3e5;
mint fact[N + 1], ifact[N + 1];
mint binom(int n, int m) { return fact[n] * ifact[n - m] * ifact[m]; }

auto solve() -> void {
    int n;
    std::cin >> n;

    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> a[i];

    std::vector<int> cnt(n + 1);
    for (int x = 1; x <= n; ++x) cnt[std::min(x, n - x + 1)] += 1;

    mint ans = 1;

    int tot = 0;
    for (int i = n; i >= 1; --i) {
        tot += cnt[i];
        if (a[i] > tot) {
            ans = 0;
            break;
        }
        ans *= binom(tot, a[i]);
        tot -= a[i];
    }
    if (tot != 0) ans = 0;

    std::cout << ans() << '\n';
}

int main() {
    fact[0] = 1;
    for (int i = 1; i <= N; ++i) fact[i] = fact[i - 1] * i;
    ifact[N] = 1 / fact[N];
    for (int i = N - 1; i >= 0; --i) ifact[i] = ifact[i + 1] * (i + 1);

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    for (auto _ : std::views::iota(0, t)) solve();
}
