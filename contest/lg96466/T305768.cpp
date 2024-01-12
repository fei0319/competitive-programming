#include <cassert>
#include <cstdio>

typedef unsigned long long ull;
typedef unsigned int uint;
typedef long long ll;

const uint mod = 3221225473u;
const int N = 20000010;

ull seed;

ull getnext() {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}

uint rd(uint l, uint r) {
    return getnext() % (r - l + 1) + l;
}

int n;
ull k;
uint b[N];

struct Matrix {
    uint a[2][2];
    Matrix() {
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                a[i][j] = 0;
    }
    Matrix operator*(const Matrix &b) const {
        Matrix res;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                for (int k = 0; k < 2; ++k)
                    res.a[i][j] =
                        (res.a[i][j] + (ull)a[i][k] * b.a[k][j]) % mod;
        return res;
    }
    void out() {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j)
                printf("%u ", a[i][j]);
            puts("");
        }
    }
    bool operator==(const Matrix &b) const {
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                if (a[i][j] != b.a[i][j])
                    return false;
        return true;
    }
} init, tran;

uint qpow(uint a, uint b) {
    uint res = 1;
    while (b) {
        if (b & 1)
            res = (ull)res * a % mod;
        a = (ull)a * a % mod, b >>= 1;
    }
    return res;
}

Matrix qpow(Matrix a, ull b) {
    Matrix res;
    res.a[0][0] = res.a[1][1] = 1;
    while (b) {
        if (b & 1)
            res = res * a;
        a = a * a, b >>= 1;
    }
    return res;
}

int main() {
    scanf("%d%llu%llu", &n, &k, &seed);
    ull sum = 0;
    for (int i = 1; i < n; ++i)
        b[i] = rd(2u, mod - 1), (sum += b[i]) %= mod;
    b[n] = mod + 1 - sum;

    init.a[0][0] = 1,
    init.a[0][1] = 2ull * qpow((ull)n * n % mod, mod - 2) % mod;

    tran.a[0][0] = ((ull)(n - 1) * (n - 1) - 1u) % mod *
                   qpow((ull)n * n % mod, mod - 2) % mod;
    tran.a[1][0] = 1, tran.a[1][1] = 1;

    //	(init * qpow(tran, 0)).out();

    //	assert(qpow(tran, 3) == tran * tran * tran);

    uint p = (init * qpow(tran, k)).a[0][0],
         f = ull(1u + mod - p) * qpow(n - 1, mod - 2) % mod;

    //	printf("%llu\n", p);

    ull ans = 0ull;
    for (int i = 1; i <= n; ++i) {
        uint v = (f + ull((ull)mod + p - f) % mod * b[i]) % mod;
        ans ^= (ull)i * (ull)v;
    }

    printf("%llu\n", ans);
}