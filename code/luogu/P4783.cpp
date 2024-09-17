#include <bits/stdc++.h>

template <int m>
class ModInt {
    int raw_;

public:
    ModInt() : raw_(0) {}
    ModInt(const auto &v) : raw_(v % m) {}
    using mint = ModInt;
    using i64 = int64_t;
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

    int value() const {
        return (raw_ + m) % m;
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
    friend mint operator/(const mint &lhs, const mint &rhs) {
        return mint{lhs} /= rhs;
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

template <typename T>
struct Matrix {
    std::vector<std::vector<T>> a{};

    Matrix() = default;
    Matrix(int n) : a(n, std::vector<T>(n)) {}

    std::optional<Matrix> inv() const {
        int n = a.size();
        Matrix a(*this), b(I(n));

        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                if (a.a[j][i].value()) {
                    if (j != i) {
                        std::swap(a.a[i], a.a[j]);
                        std::swap(b.a[i], b.a[j]);
                    }
                    break;
                }
            }

            if (!a.a[i][i].value()) {
                return std::nullopt;
            }

            {
                T iv = 1 / a.a[i][i];
                for (int j = 0; j < n; ++j) {
                    a.a[i][j] *= iv;
                    b.a[i][j] *= iv;
                }
            }

            for (int j = i + 1; j < n; ++j) {
                T f = a.a[j][i];
                for (int k = 0; k < n; ++k) {
                    a.a[j][k] -= a.a[i][k] * f;
                    b.a[j][k] -= b.a[i][k] * f;
                }
            }
        }

        for (int i = n - 1; i >= 0; --i) {
            for (int j = i - 1; j >= 0; --j) {
                T f = a.a[j][i];
                for (int k = 0; k < n; ++k) {
                    a.a[j][k] -= a.a[i][k] * f;
                    b.a[j][k] -= b.a[i][k] * f;
                }
            }
        }

        return b;
    };
    friend Matrix operator*(const Matrix &lhs, const Matrix &rhs) {
        int n = lhs.a.size();
        Matrix res(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    res.a[i][k] += lhs.a[i][j] * rhs.a[j][k];
                }
            }
        }
        return res;
    }
    static Matrix I(int n) {
        Matrix res(n);
        for (int i = 0; i < n; ++i) {
            res.a[i][i] = 1;
        }
        return res;
    }
};

using mint = ModInt<static_cast<int>(1e9 + 7)>;
using mat = Matrix<mint>;

int main() {
    int n;
    std::cin >> n;

    mat a(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int t;
            std::cin >> t;
            a.a[i][j] = t;
        }
    }

    auto res = a.inv();
    if (!res.has_value()) {
        std::cout << "No Solution\n";
        return 0;
    }

    a = res.value();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << a.a[i][j].value() << ' ';
        }
        std::cout << '\n';
    }
}
