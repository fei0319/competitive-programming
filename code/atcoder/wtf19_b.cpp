#include <bits/stdc++.h>

struct DSU {
    std::vector<int> fa;
    explicit DSU(int n) : fa(n) { std::iota(fa.begin(), fa.end(), 0); }
    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
    void merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) {
            fa[y] = x;
        }
    }
    size_t size() {
        size_t cnt{};
        for (int i : std::views::iota(0, (int)fa.size())) {
            if (find(i) == i) {
                ++cnt;
            }
        }
        return cnt;
    }
};

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

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;

int main() {
    int n, q;
    std::cin >> n >> q;

    std::vector<int> tmp{0};
    std::vector<std::pair<int, int>> ranges(q);
    for (auto &[l, r] : ranges) {
        std::cin >> l >> r;
        --l;

        tmp.push_back(l);
        tmp.push_back(r);
    }

    std::sort(tmp.begin(), tmp.end());
    tmp.resize(std::unique(tmp.begin(), tmp.end()) - tmp.begin());

    for (auto &[l, r] : ranges) {
        l = std::lower_bound(tmp.begin(), tmp.end(), l) - tmp.begin();
        r = std::lower_bound(tmp.begin(), tmp.end(), r) - tmp.begin();
    }

    auto dsu = DSU{static_cast<int>(tmp.size())};
    for (const auto &[l, r] : ranges) {
        dsu.merge(l, r);
    }

    const int m = dsu.size();
    std::vector<int> bel(tmp.size());
    {
        std::unordered_map<int, int> roots;
        for (int i : std::views::iota(0, (int)tmp.size())) {
            if (!roots.contains(dsu.find(i))) {
                const int idx = roots.size();
                roots.emplace(dsu.find(i), idx);
            }
            bel[i] = roots[dsu.find(i)];
        }
    }

    mint ans{1};
    ans *= mint::qpow(10, n - tmp.back());

    std::vector<mint> f(1 << m);
    for (int S : std::views::iota(0, 1 << m)) {
        mint &res = f[S];
        res = 1;

        auto contains = [&](int i) -> bool { return S & (1 << bel[i]); };
        auto base_f = [](int len) {
            return (mint::qpow(10, len) - 1) / 9;
        };
        for (int i = 1; i < tmp.size(); ++i) {
            if (contains(i)) {
                if (contains(i - 1)) {
                    res *= base_f(tmp[i] - tmp[i - 1]) + 1;
                } else {
                    res *= base_f(tmp[i] - tmp[i - 1]);
                }
            }
        }
    }

    std::array<std::vector<mint>, 2> dp;
    dp[0] = f;
    for (int S : std::views::iota(0, 1 << m)) {
        if (S & 1) {
            f[S] = 0;
        }
    }
    for (int _ : std::views::iota(1, 9)) {
        dp[_ & 1].assign(1 << m, 0);
        for (int S : std::views::iota(0, 1 << m)) {
            for (int T = S; T; T = (T - 1) & S) {
                dp[_ & 1][S] += dp[(_ & 1) ^ 1][T] * f[S ^ T];
            }
        }
    }
    ans *= dp[8 & 1][(1 << m) - 1];

    std::cout << ans() << '\n';
}
