struct DynamicModInt {
private:
    int raw_;
    using mint = DynamicModInt;
    using i64 = int64_t;

public:
    static int m;
    DynamicModInt() {
        raw_ = 0;
    }
    template <typename T>
    DynamicModInt(const T &v) {
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
