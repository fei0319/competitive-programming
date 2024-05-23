#include <bits/stdc++.h>

template <int m>
struct ModInt {
private:
    int raw_;
    using mint = ModInt;
    using i64 = int64_t;

public:
    ModInt() {
        raw_ = 0;
    }
    template <typename T>
    ModInt(const T &v) {
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

using i64 = int64_t;
constexpr int MOD = 998244353;
constexpr i64 _ = 1e18;
constexpr int BASE = _ % MOD;
using mint = ModInt<MOD>;

int main() {
    int n;
    std::cin >> n;

    auto add_dimension = [&](std::vector<std::vector<int>> adj,
                             std::vector<mint> f) {
        std::vector<mint> cnt(f.size());
        std::vector<int> b(n + 1);
        for (int i = n; i >= 1; --i) {
            std::vector<uint8_t> has(adj[i].size() + 1);
            for (int j = 0; j < adj[i].size(); ++j) {
                int to = adj[i][j];
                if (b[to] < has.size()) {
                    has[b[to]] = true;
                }
            }
            int mex = 0;
            while (has[mex]) {
                ++mex;
            }
            if (cnt.size() <= mex) {
                cnt.resize(mex + 1, 0);
            }
            cnt[mex] += mint::qpow(BASE, i);
            b[i] = mex;
        }

        std::vector<std::vector<int>> a;

        const int size = cnt.size();
        int tot = 0;
        while (tot < size) {
            std::vector<int> t(size);
            std::vector<uint8_t> has(size * 2);

            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < i; ++j) {
                    has[t[j]] = true;
                }
                for (int j = 0; j < a.size(); ++j) {
                    has[a[j][i]] = true;
                }

                int mex = 0;
                while (has[mex]) {
                    ++mex;
                }
                t[i] = mex;

                for (int j = 0; j < i; ++j) {
                    has[t[j]] = false;
                }
                for (int j = 0; j < a.size(); ++j) {
                    has[a[j][i]] = false;
                }
            }

            a.push_back(t);
            if (std::find(t.begin(), t.end(), size - 1) != t.end()) {
                ++tot;
            }
        }

        std::vector<mint> res;
        for (const auto &v : a) {
            mint sum = 0;
            for (int i = 0; i < v.size(); ++i) {
                if (v[i] < f.size()) {
                    sum += cnt[i] * f[v[i]];
                }
            }
            res.push_back(sum);

            // for (int i : v) {
            //     std::cerr << i << ' ';
            // }
            // std::cerr << '\n';
        }

        return res;
    };

    std::vector<mint> f{1};

    for (int _ = 0; _ < 3; ++_) {
        int m;
        std::cin >> m;

        std::vector<std::vector<int>> adj(n + 1);
        for (int i = 0; i < m; ++i) {
            int u, v;
            std::cin >> u >> v;
            if (u > v) {
                std::swap(u, v);
            }
            adj[u].push_back(v);
        }

        f = add_dimension(adj, f);
    }

    std::cout << f[0].value() << '\n';
    return 0;
}