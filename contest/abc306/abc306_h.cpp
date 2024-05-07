#include <bits/stdc++.h>

using i64 = int64_t;

template <int m>
struct static_modint {
private:
    int raw_;
    using mint = static_modint;
    using i64 = int64_t;

public:
    static_modint() {
        raw_ = 0;
    }
    template <typename T>
    static_modint(const T &v) {
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

private:
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
using mint = static_modint<MOD>;

template <class Z>
struct static_comb {
    std::vector<Z> fact_, ifact_;
    static_comb(int n) : fact_(n + 1), ifact_(n + 1) {
        fact_[0] = 1;
        for (int i = 1; i <= n; ++i) {
            fact_[i] = fact_[i - 1] * i;
        }
        ifact_[n] = 1 / fact_[n];
        for (int i = n - 1; i >= 0; --i) {
            ifact_[i] = ifact_[i + 1] * (i + 1);
        }
    }
    Z fact(int x) {
        return fact_[x];
    }
    Z ifact(int x) {
        return ifact_[x];
    }
    Z binom(int n, int m) {
        return fact_[n] * ifact_[n - m] * ifact_[m];
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> adj(n);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        std::cin >> u >> v;
        u -= 1, v -= 1;
        adj[u] |= 1 << v;
        adj[v] |= 1 << u;
    }

    static_comb<mint> comb(n);

    std::vector<int> adj_S(1 << n);
    for (int S = 1; S < (1 << n); ++S) {
        adj_S[S] = adj_S[S ^ (S & -S)] | adj[__builtin_ctz(S & -S)];
    }
    std::vector<uint8_t> is_component(1 << n);
    for (int S = 1; S < (1 << n); ++S) {
        if (S == (S & -S)) {
            is_component[S] = true;
        } else {
            for (int i = 0; i < n; ++i) {
                if ((S & (1 << i)) && is_component[S ^ (1 << i)] &&
                    (adj[i] & (S ^ (1 << i)))) {
                    is_component[S] = true;
                    break;
                }
            }
        }
    }

    std::vector<mint> g(1 << n);
    g[0] = -1;
    for (int S = 1; S < (1 << n); ++S) {
        const int P = S ^ (S & -S);
        for (int s = P;; s = (s - 1) & P) {
            const int T = s ^ (S & -S);
            if (is_component[T] && !(adj_S[T] & (S ^ T))) {
                g[S] -= g[S ^ T];
            }
            if (!s) {
                break;
            }
        }
    }

    std::vector<mint> f(1 << n);
    f[0] = 1;
    for (int S = 1; S < (1 << n); ++S) {
        for (int T = S; T; T = (T - 1) & S) {
            f[S] += f[S ^ T] * g[T];
        }
    }
    std::cout << f[(1 << n) - 1].value() << '\n';

    return 0;
}