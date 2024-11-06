#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 43, MOD = 1e9 + 7;

struct Matrix {
    int a[MAXN][MAXN]{};
    explicit Matrix(int x = 0) {
        for (int i = 0; i < MAXN; ++i) {
            a[i][i] = x;
        }
    }
    Matrix operator*(const Matrix &b) const {
        Matrix res(0);
        for (int i = 0; i < MAXN; ++i) {
            for (int j = 0; j < MAXN; ++j) {
                for (int k = 0; k < MAXN; ++k) {
                    res.a[i][k] =
                        (res.a[i][k] + (ll)a[i][j] * b.a[j][k]) % MOD;
                }
            }
        }
        return res;
    }
};

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = (ll)res * a % MOD;
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}

Matrix qpow(Matrix a, int b) {
    Matrix res = Matrix(1);
    while (b) {
        if (b & 1) res = res * a;
        a = a * a, b >>= 1;
    }
    return res;
}

int n, x, k;
void solve() {
    std::cin >> n >> x >> k;
    if (n == 1) {
        std::cout << k << '\n';
        return;
    }

    int ans = (ll)(x + k) * qpow((2 * k + 1) % MOD, n - 1) % MOD;
    Matrix a{0};
    for (int i = 0; i < x; ++i) {
        for (int j = std::max(0, i - k); j <= std::min(x - 1, i + k);
             ++j) {
            a.a[i][j] = 1;
        }
    }
    a = qpow(a, n - 1);
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < x; ++j) {
            ans = (ans - a.a[i][j]) % MOD;
        }
    }
    std::cout << (ans + MOD) % MOD << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}