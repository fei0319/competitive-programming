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

template <class Z, int b>
struct HashBase {
    std::vector<Z> bp, f;
    HashBase(std::string s) {
        int n = s.size() - 1;

        bp.resize(n + 1);
        f.resize(n + 1);

        bp[0] = 1;
        f[0] = 0;

        for (int i = 1; i <= n; ++i) {
            bp[i] = bp[i - 1] * b;
            f[i] = f[i - 1] * b + s[i];
        }
    }
    Z operator()(int l, int r) const {
        return f[r] - f[l - 1] * bp[r - l + 1];
    }
};

using u64 = uint64_t;
using i64 = int64_t;

struct StringHash {
    HashBase<ModInt<208021243>, 12339> a;
    HashBase<ModInt<162792233>, 19> b;
    HashBase<ModInt<273801947>, 114514> c;
    StringHash(std::string s) : a(s), b(s), c(s) {}
    u64 operator()(int l, int r) {
        u64 x = a(l, r).value();
        u64 y = b(l, r).value();
        u64 z = c(l, r).value();
        return (x * y + y * z + x) ^ (z * z + x);
    }
};

void solve() {
    std::string s;
    std::cin >> s;
    s = ' ' + s;

    int n = s.size() - 1;

    std::vector<int> pos;
    for (int i = 1; i <= n; ++i) {
        if (s[i] != 'a') {
            pos.push_back(i);
        }
    }

    if (pos.empty()) {
        std::cout << n - 1 << '\n';
        return;
    }

    std::vector<i64> f(n + 1);
    const int l = pos.front() - 1, r = n - pos.back();
    f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        f[i] = f[i - 1];
        int p = std::max(i - r, 0), q = std::min(l, i);
        if (p <= q) {
            f[i] += q - p + 1;
        }
    }

    StringHash h(s);

    i64 ans = 0;
    for (int len = 1; len <= pos.size(); ++len) {
        if (pos.size() % len != 0) {
            continue;
        }

        bool ok = true;
        const u64 b = h(pos[0], pos[len - 1]);
        int l = pos.front() - 1, r = n - pos.back(), mid = n;
        for (int i = len; i < pos.size(); i += len) {
            mid = std::min(mid, pos[i] - pos[i - 1] - 1);
            if (h(pos[i], pos[i + len - 1]) != b) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            continue;
        }

        ans += f[mid];
    }

    std::cout << ans << '\n';
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