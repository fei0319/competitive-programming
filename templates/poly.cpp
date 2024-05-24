template <class Z>
class Poly : public std::vector<Z> {
    static std::vector<int> rev;
    static std::vector<Z> w;
    static void dft(std::vector<Z>::iterator f, int n) {
        if (rev.size() != n) {
            rev.resize(n);
            for (int i = 0; i < n; i++) {
                rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
            }
        }
        if (w.size() < n) {
            int k = __builtin_ctz(w.size());
            w.resize(n);
            while ((1 << k) < n) {
                auto e =
                    Z::qpow(31, 1 << (__builtin_ctz(Z::mod() - 1) - k - 1));
                for (int i = 1 << (k - 1); i < (1 << k); ++i) {
                    w[i * 2] = w[i];
                    w[i * 2 + 1] = w[i] * e;
                }
                ++k;
            }
        }

        for (int i = 0; i < n; ++i) {
            if (i < rev[i]) {
                std::swap(f[i], f[rev[i]]);
            }
        }
        for (int i = 1; i < n; i *= 2) {
            for (int j = 0; j < n; j += i * 2) {
                auto g = f + j, h = f + j + i;
                for (int k = 0; k < i; ++k) {
                    const Z p = g[k], q = h[k] * w[i + k];
                    g[k] = p + q, h[k] = p - q;
                }
            }
        }
    }

    static void idft(std::vector<Z>::iterator f, int n) {
        std::reverse(f + 1, f + n);
        dft(f, n);
        const Z inv = (1 - Z::mod()) / n;
        for (int i = 0; i < n; ++i) {
            f[i] *= inv;
        }
    }

public:
    using std::vector<Z>::vector;
    using std::vector<Z>::size;
    using std::vector<Z>::resize;
    using std::vector<Z>::at;

    Poly &operator+=(const Poly &rhs) {
        if (rhs.size() > size()) {
            resize(rhs.size());
        }
        for (int i = 0; i < rhs.size(); ++i) {
            this->operator[](i) += rhs[i];
        }
        return *this;
    }

    Poly &operator-=(const Poly &rhs) {
        if (rhs.size() > size()) {
            resize(rhs.size());
        }
        for (int i = 0; i < rhs.size(); ++i) {
            this->operator[](i) -= rhs[i];
        }
        return *this;
    }
    friend Poly operator+(const Poly &lhs, const Poly &rhs) {
        return Poly(lhs) += rhs;
    }
    friend Poly operator-(const Poly &lhs, const Poly &rhs) {
        return Poly(lhs) -= rhs;
    }

    Poly &operator*=(const Z &rhs) {
        for (Z &i : *this) {
            i *= rhs;
        }
        return *this;
    }
    friend Poly operator*(const Poly &lhs, const Z &rhs) {
        return Poly(lhs) *= rhs;
    }

    friend Poly operator*(const Poly &lhs, const Poly &rhs) {
        int N = 1, n = lhs.size() + rhs.size() - 1;

        while (N < n) {
            N *= 2;
        }

        Poly f(N), g(N);
        std::copy(lhs.begin(), lhs.end(), f.begin());
        std::copy(rhs.begin(), rhs.end(), g.begin());

        dft(f.begin(), N);
        dft(g.begin(), N);
        for (int i = 0; i < N; ++i) {
            f[i] *= g[i];
        }
        idft(f.begin(), N);
        f.resize(n);

        return f;
    }

    Poly prefix(int len) const {
        Poly f(*this);
        f.resize(len);
        return f;
    }
    Poly inv() const {
        Poly f{Z(1) / at(0)};
        for (int i = 1; i < size(); i *= 2) {
            f = (f * 2 - f * f * prefix(i * 2)).prefix(i * 2);
        }
        f.resize(size());
        return f;
    }
};

template <class Z>
std::vector<int> Poly<Z>::rev;

template <class Z>
std::vector<Z> Poly<Z>::w{0, 1};
