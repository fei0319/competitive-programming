#include <bits/stdc++.h>

template <int m>
class ModInt {
    int raw_;

public:
    using mint = ModInt;
    using i64 = int64_t;

    ModInt() : raw_(0) {}
    ModInt(const auto &v) : raw_(v % m) {}

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

    friend mint operator+(const mint &lhs, const mint &rhs) {
        return mint{lhs} += rhs;
    }
    friend mint operator-(const mint &lhs, const mint &rhs) {
        return mint{lhs} -= rhs;
    }
    friend mint operator*(const mint &lhs, const mint &rhs) {
        return mint{lhs} *= rhs;
    }
};

using mint = ModInt<998244353>;

std::vector<mint> conv(const std::vector<mint> &f, const std::vector<mint> &g,
                       int n) {
    if (f.empty() || g.empty()) {
        return {};
    }
    std::vector<mint> res(std::min<int>(n, f.size() + g.size() - 1));
    for (int i = 0; i < f.size(); ++i) {
        if (f[i].value() == 0) {
            continue;
        }
        for (int j = 0; j < g.size() && i + j < res.size(); ++j) {
            res[i + j] += f[i] * g[j];
        }
    }
    while (!res.empty() && res.back().value() == 0) {
        res.pop_back();
    }
    return res;
}

void small_k(int n, int k, const std::vector<std::vector<int>> &adj) {
    std::vector<std::vector<mint>> dp(n + 1);

    auto dfs = [&](auto self, int node, int fa) -> void {
        dp[node] = std::vector<mint>{0, 1};
        for (int to : adj[node]) {
            if (to == fa) {
                continue;
            }
            self(self, to, node);
            dp[node] = conv(dp[node], dp[to], k + 2);
        }
        if (k < dp[node].size()) {
            dp[node][0] += dp[node][k];
        }
        if (k + 1 < dp[node].size()) {
            dp[node][0] += dp[node][k + 1];
        }
    };
    dfs(dfs, 1, 0);

    if (0 < dp[1].size()) {
        std::cout << dp[1][0].value() << '\n';
    } else {
        std::cout << "0\n";
    }
}

void great_k(int n, int k, const std::vector<std::vector<int>> &adj) {
    auto [quot, rem] = div(n, k);
    if (rem > quot) {
        std::cout << "0\n";
        return;
    }

    std::vector<int> sz(n + 1);
    std::vector<std::vector<mint>> dp(n + 1);
    std::vector<mint> g(n + 1); // root in a (k + 1) chunk
    auto dfs = [&](auto self, int node, int fa) -> void {
        sz[node] = 1;
        dp[node] = std::vector<mint>{1};
        for (int to : adj[node]) {
            if (to == fa) {
                continue;
            }
            self(self, to, node);

            std::vector<mint> F(dp[node].size() + dp[to].size());
            mint ng = 0;
            for (int x = 0; x < dp[node].size(); ++x) {
                const int cx = (sz[node] + k - x - 1) % k + 1;
                for (int y = 0; y < dp[to].size(); ++y) {
                    const int cy = (sz[to] + k - y - 1) % k + 1;
                    if (cx + cy == k + 1) {
                        ng += dp[node][x] * dp[to][y];
                    }
                    if (cx + cy <= k || cy == k) {
                        F[x + y] += dp[node][x] * dp[to][y];
                    }
                }
                if ((dp[node][x] * g[to]).value()) {
                    if (F.size() <= x + (sz[to] % k)) {
                        F.resize(x + (sz[to] % k) + 1);
                    }
                    F[x + (sz[to] % k)] += dp[node][x] * g[to];
                }
            }
            for (int y = 0; y < dp[to].size(); ++y) {
                const int cy = (sz[to] + k - y - 1) % k + 1;
                if (cy == k) {
                    ng += g[node] * dp[to][y];
                }
            }
            ng += g[node] * g[to];

            while (!F.empty() && F.back().value() == 0) {
                F.pop_back();
            }
            sz[node] += sz[to];
            dp[node].swap(F);
            g[node] = ng;
        }
    };
    dfs(dfs, 1, 0);

    mint ans = g[1];
    if (rem < dp[1].size()) {
        ans += dp[1][rem];
    }
    std::cout << ans.value() << '\n';
}

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<std::vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (k + 1 < 350) {
        small_k(n, k, adj);
    } else {
        great_k(n, k, adj);
    }
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
