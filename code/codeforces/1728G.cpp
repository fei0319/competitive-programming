#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 2e5 + 19, MAXM = 17;
const int MOD = 998244353;

int d, n, m;
int l[MAXN], p[MAXN];
int v[MAXM][MAXM];

struct Matrix {
    int a[MAXM][MAXM]{};
    Matrix operator*(const Matrix &b) const {
        Matrix res;
        for (int i = 0; i < MAXM; ++i) {
            for (int j = 0; j < MAXM; ++j) {
                for (int k = 0; k < MAXM; ++k) {
                    res.a[i][k] =
                        (res.a[i][k] + (ll)a[i][j] * b.a[j][k]) % MOD;
                }
            }
        }
        return res;
    }
    static constexpr Matrix E() {
        Matrix res;
        for (int i = 0; i < MAXM; ++i) {
            res.a[i][i] = 1;
        }
        return res;
    }
};

Matrix get(int x) {
    Matrix res;
    for (int i = 0; i < m; ++i) {
        res.a[i][i] = std::min(std::abs<int>(x - p[i]), d + 1);
        int l = std::abs<int>(x - p[i]), r;
        for (int j = i; j < m; ++j) {
            l = std::max(l, std::abs<int>(x - p[j]));
            r = std::min(std::abs<int>(x - p[j + 1]) - 1, d);
            if (l <= r) {
                res.a[i][j + 1] = r - l + 1;
            }
        }
    }
    res.a[m][m] = d + 1;

    return res;
}

Matrix pre[MAXN], suf[MAXN];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> d >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> l[i];
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> p[i];
    }

    std::sort(l + 1, l + 1 + n);
    std::sort(p, p + m);
    p[m] = 1e9;

    pre[0] = suf[n + 1] = Matrix::E();
    for (int i = 1; i <= n; ++i) {
        pre[i] = suf[i] = get(l[i]);
    }
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] * pre[i];
    }
    for (int i = n; i >= 1; --i) {
        suf[i] = suf[i] * suf[i + 1];
    }

    int q;
    std::cin >> q;
    while (q--) {
        int f;
        std::cin >> f;

        int p = std::lower_bound(l + 1, l + 1 + n, f) - l;
        Matrix a = pre[p - 1], b = get(f), c = suf[p];
        int res = 0;
        for (int i = 0; i < MAXM; ++i) {
            for (int j = 0; j < MAXM; ++j) {
                res = (res + (ll)a.a[0][i] * b.a[i][j] % MOD * c.a[j][m]) %
                      MOD;
            }
        }
        std::cout << res << '\n';
    }

    return 0;
}