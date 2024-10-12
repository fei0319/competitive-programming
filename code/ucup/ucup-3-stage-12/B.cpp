#include <bits/stdc++.h>

class ModInt {
    uint32_t raw;
    using mint = ModInt;
    using i64 = int64_t;

public:
    static uint32_t m;
    ModInt() : raw(0) {}
    ModInt(auto v) {
        v %= m;
        if (v < 0) {
            v += m;
        }
        raw = v;
    }
    int operator()() const {
        return raw;
    }

    mint &operator+=(const mint &rhs) {
        raw += rhs.raw;
        if (raw >= m) {
            raw -= m;
        }
        return *this;
    }
    mint &operator-=(const mint &rhs) {
        if (raw > rhs.raw) {
            raw -= rhs.raw;
        } else {
            raw = m - (rhs.raw - raw);
            if (raw >= m) {
                raw -= m;
            }
        }
        return *this;
    }
    mint &operator*=(const mint &rhs) {
        raw = (i64)raw * rhs.raw % m;
        return *this;
    }
    mint &operator/=(const mint &rhs) {
        return *this *= qpow(rhs, m - 2);
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

    static mint qpow(mint a, i64 b) {
        mint res = 1;
        while (b) {
            if (b & 1) {
                res *= a;
            }
            a *= a, b >>= 1;
        }
        return res;
    }
};

using mint = ModInt;
uint32_t mint::m;

void solve() {
    int n, p;
    std::cin >> n >> p;
    mint::m = p;

    std::vector<mint> a(n * 2 + 1);
    {
        int rawb, rawA, rawB;
        std::cin >> rawb >> rawA >> rawB;
        mint b = rawb, A = rawA, B = rawB;
        for (int i = 1; i <= n * 2; ++i) {
            b = A * b + B;
            a[i] = a[i - 1] + b + 1;
        }
    }

    std::vector<mint> fact, ifact;
    auto init = [&](int N) -> void {
        fact.resize(N + 1);
        ifact.resize(N + 1);
        fact[0] = 1;
        for (int i = 1; i <= N; ++i) {
            fact[i] = fact[i - 1] * i;
        }
        ifact[N] = 1 / fact[N];
        for (int i = N - 1; i >= 0; --i) {
            ifact[i] = ifact[i + 1] * (i + 1);
        }
    };
    init(n * 2);
    auto binom = [&](int n, int m) {
        return fact[n] * ifact[n - m] * ifact[m];
    };
    auto H = [&](int n) -> mint {
        if (n == 0) {
            return 1;
        }
        return binom(n * 2, n) - binom(n * 2, n - 1);
    };

    std::vector<mint> f(n);
    for (int i = 0; i < n; ++i) {
        f[i] = H(i) * H(n - i - 1);
    }

    // a_l a_r
    // d = r - l - 1
    // H_{d/2} * H_{n-d/2-1}
    // f[d/2]

    // g[i] = sum f_0...i/2-1

    std::vector<mint> g(n * 2 + 1);
    for (int i = 2; i <= n * 2; ++i) {
        g[i] = g[i - 2] + f[i / 2 - 1];
    }

    mint ans = 0;
    for (int i = 1; i <= n * 2; ++i) {
        ans += (g[i] - g[n * 2 - i + 1]) * a[i];
    }

    std::cout << (ans / H(n))() << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
}
