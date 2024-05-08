#include <bits/stdc++.h>

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

constexpr int MOD = 998244353;
constexpr int N = 3000;
using mint = static_modint<MOD>;

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

    // std::vector<int> spj{1, 1, 1, 5};
    // if (n < spj.size()) {
    //     std::cout << spj[n] << '\n';
    //     return 0;
    // }

    int rt = 0;
    while (adj[rt].size() == 1) {
        ++rt;
    }

    int n_leaves = 0;
    for (int i = 0; i < n; ++i) {
        n_leaves += adj[i].size() == 1;
    }

    std::vector<mint> f(n), g(n);
    std::vector<int> size(n), leaves(n);
    std::vector<std::bitset<N>> in(n);
    auto dfs0 = [&](auto self, int node, int fa) -> void {
        for (int to : adj[node]) {
            if (to == fa) {
                continue;
            }
            self(self, to, node);

            size[node] += size[to];
            leaves[node] += leaves[to];
            in[node] |= in[to];
        }
        size[node] += 1;
        leaves[node] += (adj[node].size() == 1);
        in[node].set(node);

        auto calc = [&](bool flag) -> mint {
            int available_leaves = 0;
            mint res = 1, tot = 1;
            for (int i = 0; i < n; ++i) {
                if (adj[i].size() == 1) {
                    if (flag ? in[node].test(i)
                             : (!in[node].test(i) || i == node)) {
                        ++available_leaves;
                    } else {
                        int num =
                            flag ? size[node] - leaves[node] + available_leaves
                                 : (n - size[node] + 1) -
                                       (n_leaves - leaves[node]) +
                                       available_leaves;
                        if (num == 0) {
                            continue;
                        }
                        res *= mint::qpow(2, num) - 1;
                        tot *= mint::qpow(2, num);
                    }
                }
            }
            return res / tot;
        };

        f[node] = calc(true);
        g[node] = calc(false); // only valid for non-leaf nodes
        if (node == rt) {
            g[node] = 1;
        }
    };
    dfs0(dfs0, rt, -1);

    auto convolution = [](const std::vector<mint> &f,
                          const std::vector<mint> &g) {
        std::vector<mint> res(f.size() + g.size() - 1);
        for (int x = 0; x < f.size(); ++x) {
            for (int y = 0; y < g.size(); ++y) {
                res[x + y] += f[x] * g[y];
            }
        }
        return res;
    };
    auto addition = [](const std::vector<mint> &f, const std::vector<mint> &g) {
        std::vector<mint> res(f);
        if (g.size() > f.size()) {
            res.resize(g.size());
        }
        for (int i = 0; i < g.size(); ++i) {
            res[i] += g[i];
        }
        return res;
    };

    // std::fill(f.begin(), f.end(), 1);
    // std::fill(g.begin(), g.end(), 1);

    std::vector<std::vector<mint>> F(n);
    std::vector<std::vector<mint>> dp(n);
    auto dfs1 = [&](auto self, int node, int fa) -> void {
        dp[node].assign(1, 1);
        F[node].assign(1, 1);
        for (int to : adj[node]) {
            if (to == fa) {
                continue;
            }
            self(self, to, node);

            dp[node] = convolution(dp[node], dp[to]);
            F[node] = convolution(F[node], F[to]);
        }

        auto tmp = convolution(dp[node], std::vector<mint>{0, g[node]});
        if (adj[node].size() == 1) {
            tmp[1] += f[node] - g[node];
        } else {
            tmp[1] += (f[node] - 1) * g[node];
        }
        F[node] = addition(F[node], tmp);

        dp[node] = convolution(dp[node], std::vector<mint>{1, 1});
        dp[node][1] -= 1;
        dp[node][1] += f[node];

        std::cerr << "dp_" << node << " = ";
        for (int i = 0; i < dp[node].size(); ++i) {
            std::cerr << dp[node][i].value() << ' ';
        }
        std::cerr << '\n';
    };
    dfs1(dfs1, rt, -1);

    mint all = mint::qpow(2, n * (n - 1) / 2);
    std::cerr << all.value() << '\n';
    for (int i = 0; i < F[rt].size(); ++i) {
        F[rt][i] *= all;
        std::cerr << std::format("F_{}={}\n", i, F[rt][i].value());
    }

    return 0;
}