#include <bits/stdc++.h>

template <int m>
struct ModInt {
private:
    int raw_;
    using mint = ModInt;
    using i64 = int64_t;

public:
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

using mint = ModInt<998244353>;
constexpr int K = 20;

struct DP {
    int n;
    std::array<std::array<std::array<mint, K + 1>, 2>, 2> a;
    std::array<std::array<mint, K + 1>, 2> l, r;
    std::array<mint, K + 1> res;
    friend DP operator*(const DP &lhs, const DP &rhs) {
        DP res;
        res.n = lhs.n + rhs.n;
        const int Ln = lhs.n / 2, Rn = rhs.n / 2;

        for (int k = 0; k <= K; ++k) {
            res.res[k] += lhs.res[k];
            res.res[k] += rhs.res[k];
            res.res[k] += lhs.l[0][k] * rhs.n;
            res.res[k] += lhs.n * rhs.r[0][k];
        }
        for (int mid = 0; mid < 2; ++mid) {
            for (int x = 0; x <= K && x <= Ln; ++x) {
                for (int y = 0; x + y + mid <= K && y <= Rn; ++y) {
                    res.res[x + y + mid] += lhs.l[mid][x] * rhs.r[mid][y];
                }
            }
        }

        for (int mid = 0; mid < 2; ++mid) {
            for (int f = 0; f < 2; ++f) {
                for (int x = 0; x <= K && x <= Ln; ++x) {
                    for (int y = 0; x + y + mid <= K && y <= Rn; ++y) {
                        res.l[f][x + y + mid] +=
                            lhs.l[mid][x] * rhs.a[mid][f][y];
                        res.r[f][x + y + mid] +=
                            lhs.a[f][mid][x] * rhs.r[mid][y];
                    }
                }
            }
        }
        for (int f = 0; f < 2; ++f) {
            for (int k = 0; k <= K; ++k) {
                res.l[f][k] += lhs.l[f][k];
                res.l[f][k] += rhs.l[f][k] + lhs.n * rhs.a[0][f][k];

                res.r[f][k] += rhs.r[f][k];
                res.r[f][k] += lhs.r[f][k] + lhs.a[f][0][k] * rhs.n;
            }
        }

        for (int left = 0; left < 2; ++left) {
            for (int right = 0; right < 2; ++right) {
                for (int k = 0; k <= K; ++k) {
                    res.a[left][right][k] += lhs.a[left][right][k];
                    res.a[left][right][k] += rhs.a[left][right][k];
                }
                for (int mid = 0; mid < 2; ++mid) {
                    for (int x = 0; x <= K && x <= Ln; ++x) {
                        for (int y = 0; x + y + mid <= K && y <= Rn; ++y) {
                            res.a[left][right][x + y + mid] +=
                                lhs.a[left][mid][x] * rhs.a[mid][right][y];
                        }
                    }
                }
            }
        }
        return res;
    }
};

int topbit(int x) {
    int res = 0;
    while (x > 1) {
        x >>= 1;
        ++res;
    }
    return res;
}

void monoid_product(const std::vector<DP> &vec,
                    const std::vector<std::pair<int, int>> &query, auto f) {
    const int n = vec.size();
    std::vector<std::vector<int>> buk(n);
    for (int id = 0; id < query.size(); ++id) {
        auto [l, r] = query[id];
        if (l == r) {
            continue;
        }
        int k = topbit(l ^ r);
        buk[r >> k << k].push_back(id);
    }

    std::vector<DP> dp(n);
    for (int mid = 1; mid < n; ++mid) {
        int min = mid, max = mid;
        for (int id : buk[mid]) {
            auto [l, r] = query[id];
            min = std::min(min, l);
            max = std::max(max, r);
        }
        dp[mid - 1] = vec[mid - 1];
        for (int i = mid - 2; i >= min; --i) {
            dp[i] = vec[i] * dp[i + 1];
        }
        dp[mid] = vec[mid];
        for (int i = mid + 1; i <= max; ++i) {
            dp[i] = dp[i - 1] * vec[i];
        }
        for (int id : buk[mid]) {
            auto [l, r] = query[id];
            f(dp[l], dp[r], id);
        }
    }
}

std::mt19937 rng(std::random_device{}());
int randint(int l, int r) {
    return rng() % (r - l + 1) + l;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::string s;
    std::cin >> s;
    // s.resize(n, '(');
    // for (int i = 0; i < n; ++i) {
    //     if (randint(0, 1)) {
    //         s[i] = ')';
    //     }
    // }

    std::vector<std::pair<int, int>> query(q);
    std::vector<int> ops(q), ks(q);
    for (int i = 0; i < q; ++i) {
        int l, r;

        std::cin >> ops[i] >> l >> r >> ks[i];
        // ops[i] = randint(1, 2), l = randint(1, n), r = randint(1, n),
        // ks[i] = randint(1, K);
        // if (l > r) {
        //     std::swap(l, r);
        // }

        --l, --r;
        query[i] = {l, r};
    }

    std::vector<DP> vec(n);
    for (int i = 0; i < n; ++i) {
        vec[i].n = 1;
        auto &a = vec[i].a;
        auto &l = vec[i].l, &r = vec[i].r;
        if (s[i] == '(') {
            a[0][1][0] = 1;
            l[1][0] = 1;
        } else {
            a[1][0][0] = 1;
            r[1][0] = 1;
        }
    }

    std::vector<mint> ans(q);
    auto f = [&](const DP &L, const DP &R, int id) {
        const int k = ks[id];
        mint &res = ans[id];

        if (ops[id] == 1) {
            res += L.a[0][0][k];
            res += R.a[0][0][k];
            for (int i = 0; i <= k; ++i) {
                res += L.a[0][0][i] * R.a[0][0][k - i];
                if (i + 1 <= k) {
                    res += L.a[0][1][i] * R.a[1][0][k - i - 1];
                }
            }
        } else {
            res += L.res[k];
            res += R.res[k];
            res += L.l[0][k] * R.n;
            res += L.n * R.r[0][k];
            for (int mid = 0; mid < 2; ++mid) {
                for (int x = 0; x + mid <= k; ++x) {
                    res += L.l[mid][x] * R.r[mid][k - mid - x];
                }
            }
        }
    };
    monoid_product(vec, query, f);

    for (const auto &i : ans) {
        std::cout << i.value() << '\n';
    }
}
