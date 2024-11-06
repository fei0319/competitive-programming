#include <bits/stdc++.h>

template <int m>
struct static_modint {
private:
    int raw_;
    using mint = static_modint;
    using i64 = int64_t;

public:
    static_modint() { raw_ = 0; }
    template <typename T>
    static_modint(const T &v) {
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

template <class Z>
struct static_comb {
    std::vector<Z> fact_, ifact_;
    static_comb(int n) : fact_(n), ifact_(n) {
        fact_[0] = 1;
        for (int i = 1; i < n; ++i) {
            fact_[i] = fact_[i - 1] * i;
        }
        ifact_[n - 1] = 1 / fact_[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            ifact_[i] = ifact_[i + 1] * (i + 1);
        }
    }
    Z fact(int x) { return fact_[x]; }
    Z ifact(int x) { return ifact_[x]; }
    Z binom(int n, int m) { return fact_[n] * ifact_[n - m] * ifact_[m]; }
};

using i64 = int64_t;

template <class T>
constexpr T qpow(T a, i64 b) {
    T res = 1;
    while (b) {
        if (b & 1) {
            res *= a;
        }
        a *= a, b >>= 1;
    }
    return res;
}

constexpr int MOD = 998244353;
constexpr int N = 3000;
using mint = static_modint<MOD>;
using poly = std::vector<mint>;

int main() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (n <= 2) {
        std::cout << 1 << '\n';
        return 0;
    }

    int n_l = 0;
    for (int i = 0; i < n; ++i) {
        n_l += adj[i].size() == 1;
    }
    int rt = 0;
    while (adj[rt].size() == 1) {
        ++rt;
    }

    mint ans = 0;

    static_comb<mint> comb(n + 1);
    std::vector<int> sz(n), leaf(n);
    auto dfs = [&](auto self, int node, int fa) -> void {
        if (adj[node].size() == 1) {
            sz[node] = 1;
            leaf[node] = 1;
            return;
        }

        sz[node] = 1;
        std::vector<mint> f{1};
        for (int to : adj[node]) {
            if (to == fa) {
                continue;
            }
            self(self, to, node);

            std::vector<mint> n_f(f.size() + leaf[to]);
            for (int i = 0; i < f.size(); ++i) {
                for (int j = 0; j <= leaf[to]; ++j) {
                    n_f[i + j] +=
                        f[i] *
                        qpow(mint(2), (sz[node] - i) * (sz[to] - j)) *
                        comb.binom(leaf[to], j) *
                        qpow(mint(2), sz[to] * (sz[to] - 1) / 2);
                }
            }
            f = std::move(n_f);
            sz[node] += sz[to];
            leaf[node] += leaf[to];
        }

        for (int i = 0; i < f.size(); ++i) {
            mint res = f[i];
            if (node != rt) {
                res *= qpow(mint(2), (n - sz[node] - (n_l - leaf[node])) *
                                         (sz[node] - i));
                res *= qpow(qpow(mint(2), sz[node] - i) - 1,
                            n_l - leaf[node]);
                res *=
                    qpow(mint(2), (n - sz[node]) * (n - sz[node] - 1) / 2);
            }
            ans += res * (i & 1 ? -1 : 1);
        }

        if (node != rt) {
            for (int i = 0; i <= leaf[node]; ++i) {
                mint res = qpow(mint(2), sz[node] * (sz[node] - 1) / 2) *
                           comb.binom(leaf[node], i);
                res *= qpow(mint(2), (n - sz[node] - (n_l - leaf[node])) *
                                         (sz[node] - i));
                res *= qpow(qpow(mint(2), sz[node] - i) - 1,
                            n_l - leaf[node]);
                res *=
                    qpow(mint(2), (n - sz[node]) * (n - sz[node] - 1) / 2);
                ans -= res * (i & 1 ? -1 : 1);
            }
        }
    };
    dfs(dfs, rt, -1);

    std::cout << ans.value() << '\n';

    return 0;
}