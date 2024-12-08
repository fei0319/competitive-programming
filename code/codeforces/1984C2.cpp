#include <bits/stdc++.h>

template <int m>
struct ModInt {
private:
    int raw_;
    using mint = ModInt;
    using i64 = int64_t;

public:
    ModInt() { raw_ = 0; }
    template <typename T>
    ModInt(const T &v) {
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

using i64 = int64_t;

constexpr int MOD = 998244353;
using mint = ModInt<MOD>;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }

    i64 l = 0, r = 0;
    mint way_l = 0, way_r = 1;
    for (int i = 1; i <= n; ++i) {
        i64 nl, nr;
        nl = std::min({l + a[i], llabs(l + a[i]), llabs(r + a[i])});
        nr = std::max({r + a[i], llabs(l + a[i]), llabs(r + a[i])});

        mint nway_l = 0, nway_r = 0;
        if (nl == l + a[i]) {
            nway_l += way_l;
        }
        if (nl == llabs(l + a[i])) {
            nway_l += way_l;
        }
        if (nl == r + a[i]) {
            nway_l += way_r;
        }
        if (nl == llabs(r + a[i])) {
            nway_l += way_r;
        }

        if (nr == l + a[i]) {
            nway_r += way_l;
        }
        if (nr == llabs(l + a[i])) {
            nway_r += way_l;
        }
        if (nr == r + a[i]) {
            nway_r += way_r;
        }
        if (nr == llabs(r + a[i])) {
            nway_r += way_r;
        }

        if (nl == nr) {
            nway_l = 0;
        }

        l = nl;
        r = nr;

        way_l = nway_l;
        way_r = nway_r;
    }

    std::cout << way_r.value() << '\n';
}

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
}