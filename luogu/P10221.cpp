#include <bits/stdc++.h>

using i64 = int64_t;
constexpr int MOD = 1e9 + 7;

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

constexpr int N = 17;

struct poly_p {
    std::array<mint, N> f{};
    static poly_p from_integer(int x) {
        poly_p res;
        std::fill(res.f.begin(), res.f.end(), x);
        return res;
    }
    static poly_p from_coeff(std::array<mint, N> c) {
        poly_p res;
        for (int i = 0; i < N; ++i) {
            mint x = 1;
            for (int j = 0; j < N; ++j) {
                res.f[i] += c[j] * x;
                x *= i;
            }
        }
        return res;
    }
    std::array<mint, N> to_coeff() const {
        std::array<std::array<mint, N + 1>, N> b;
        for (int i = 0; i < N; ++i) {
            mint x = 1;
            for (int j = 0; j < N; ++j) {
                b[i][j] = x;
                x *= i;
            }
            b[i][N] = f[i];
        }
        for (int i = 0; i < N; ++i) {
            for (int j = i; j < N; ++j) {
                if (b[j][i].value() != 0) {
                    std::swap(b[i], b[j]);
                    break;
                }
            }

            mint div = 1 / b[i][i];
            for (int j = 0; j < N + 1; ++j) {
                b[i][j] *= div;
            }
            for (int j = i + 1; j < N; ++j) {
                mint mul = b[j][i];
                for (int k = i; k < N + 1; ++k) {
                    b[j][k] -= b[i][k] * mul;
                }
            }
        }
        for (int i = N - 1; i >= 0; --i) {
            for (int j = i - 1; j >= 0; --j) {
                b[j][N] -= b[i][N] * b[j][i];
            }
        }
        std::array<mint, N> res;
        for (int i = 0; i < N; ++i) {
            res[i] = b[i][N];
        }
        return res;
    }
    poly_p &operator+=(const poly_p &rhs) {
        for (int i = 0; i < N; ++i) {
            f[i] += rhs.f[i];
        }
        return *this;
    }
    poly_p &operator*=(const poly_p &rhs) {
        for (int i = 0; i < N; ++i) {
            f[i] *= rhs.f[i];
        }
        return *this;
    }
    friend poly_p operator+(const poly_p &lhs, const poly_p &rhs) {
        return poly_p(lhs) += rhs;
    }
    friend poly_p operator*(const poly_p &lhs, const poly_p &rhs) {
        return poly_p(lhs) *= rhs;
    }
};

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<std::vector<int>> adj(n);
    std::vector<int> in_deg(n);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        std::cin >> u >> v;
        u -= 1, v -= 1;
        adj[u].push_back(v);
        in_deg[v] += 1;
    }

    std::vector<int> pred(n);
    std::queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (in_deg[i] == 0) {
            q.push(i);
        }
        pred[i] = 1 << i;
    }
    while (!q.empty()) {
        const int node = q.front();
        q.pop();
        for (int to : adj[node]) {
            --in_deg[to];
            pred[to] |= pred[node];
            if (in_deg[to] == 0) {
                q.push(to);
            }
        }
    }

    if (std::any_of(in_deg.begin(), in_deg.end(), std::identity())) {
        std::cout << "0\n";
        return 0;
    }

    std::vector<int> pred_S(1 << n);
    for (int i = 1; i < (1 << n); ++i) {
        pred_S[i] = pred_S[i ^ (i & -i)] | pred[__builtin_ctz(i & -i)];
    }

    std::vector<mint> topo(1 << n);
    topo[0] = 1;
    for (int S = 1; S < (1 << n); ++S) {
        for (int i = 0; i < n; ++i) {
            if (S & (1 << i)) {
                if (!((1 << i) & pred_S[S ^ (1 << i)])) {
                    topo[S] += topo[S ^ (1 << i)];
                }
            }
        }
    }

    std::vector<std::array<mint, N>> g(1 << n);

    g[0][0] = 1;
    for (int S = 1; S < (1 << n); ++S) {
        const int P = S ^ (S & -S);
        for (int s = P;; s = (s - 1) & P) {
            const int T = s ^ (S & -S);
            if (!(pred_S[T] & (S ^ T)) && !(pred_S[S ^ T] & T)) {
                for (int c = __builtin_popcount(S ^ T); c >= 0; --c) {
                    g[S][c + 1] += g[S ^ T][c] * topo[T];
                }
            }
            if (!s) {
                break;
            }
        }
    }

    std::vector<poly_p> h(1 << n), f(1 << n);
    for (int S = 1; S < (1 << n); ++S) {
        for (int c = 2; c <= n; c += 2) {
            g[S][c] *= -1;
        }
        h[S] = poly_p::from_coeff(g[S]);
    }

    f[0] = poly_p::from_integer(1);
    for (int S = 1; S < (1 << n); ++S) {
        for (int T = S; T; T = (T - 1) & S) {
            if (!(pred_S[S ^ T] & T)) {
                f[S] += f[S ^ T] * h[T];
            }
        }
    }

    auto res = f[(1 << n) - 1].to_coeff();

    static_comb<mint> comb(n + 1);
    mint ans;
    for (int i = 1; i <= k + 1; ++i) {
        ans += res[i] * comb.fact(i) * comb.binom(k + 1, i);
    }
    ans *= comb.fact(k) * comb.ifact(n);
    for (int i = 1; i <= k; ++i) {
        ans /= n + i;
    }

    std::cout << ans.value() << '\n';

    return 0;
}