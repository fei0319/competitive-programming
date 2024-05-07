template <class Z>
class NTT {
    static std::vector<int> rev;
    static void dft(std::vector<Z>::iterator f, int n, int b) {
        std::vector<Z> w(n);
        for (int i = 0; i < n; ++i) {
            if (i < rev[i]) {
                std::swap(f[i], f[rev[i]]);
            }
        }
        for (int i = 2; i <= n; i <<= 1) {
            w[0] = 1, w[1] = Z::qpow(3, (Z::mod() - 1) / i);
            if (b == -1) {
                w[1] = 1 / w[1];
            }
            for (int j = 2; j < i / 2; ++j) {
                w[j] = w[j - 1] * w[1];
            }
            for (int j = 0; j < n; j += i) {
                auto g = f + j, h = f + j + i / 2;
                for (int k = 0; k < i / 2; ++k) {
                    Z p = g[k], q = h[k] * w[k];
                    g[k] = p + q, h[k] = p - q;
                }
            }
        }
    }

public:
    static std::vector<int> convolution(std::vector<Z> f, std::vector<Z> g) {
        int N = 1, n = f.size() + g.size() - 1;

        while (N < n) {
            N <<= 1;
        }
        rev.resize(N);
        rev[0] = 0;
        for (int i = 1; i < N; ++i) {
            rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? N >> 1 : 0);
        }

        f.resize(N);
        g.resize(N);
        dft(f.begin(), N, 1);
        dft(g.begin(), N, 1);
        for (int i = 0; i < N; ++i) {
            f[i] *= g[i];
        }
        dft(f.begin(), N, -1);
        f.resize(n);

        const Z inv = Z(1) / N;
        for (auto &i : f) {
            i *= inv;
        }
        return f;
    }
};