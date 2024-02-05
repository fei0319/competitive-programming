#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 5e3 + 19;

constexpr int qpow(int a, int b, int p) {
    int res = 1;
    while (b) {
        if (b & 1)
            res = (ll)res * a % p;
        a = (ll)a * a % p, b >>= 1;
    }
    return res;
}

int n, m;

int f[MAXN];
// # of rated sequences
// f_i = 2^{i - 2} - \sum F_j * H_{i - j * 2}

int g[MAXN];
// # of sequences of triple pairs
// g_i = \sum g_{i - j * 3 - k} * f_j where k >= 1
// g_i = \sum G_{i - j * 3 - 1} * f_j

int F[MAXN];
// convolution(f, f)

int G[MAXN];
// prefix sum of g

int H[MAXN];
// H_i = 1 + \sum g_j * (i - j - 1) where j < i - 1

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;

    f[1] = 1;
    g[1] = 0;
    F[1] = 0;
    G[1] = 0;
    H[1] = 1;
    for (int i = 2; i <= n; ++i) {
        f[i] = qpow(2, i - 2, m);
        for (int j = 2; j * 2 < i; ++j) {
            f[i] = (f[i] - (ll)F[j] * H[i - j * 2]) % m;
        }
        if (i % 3 == 0) {
            g[i] = f[i / 3];
        }
        for (int j = 1; j * 3 < i; ++j) {
            g[i] = (g[i] + (ll)G[i - j * 3 - 1] * f[j]) % m;
        }

        for (int j = 1; j < i; ++j) {
            F[i] = (F[i] + (ll)f[j] * f[i - j]) % m;
        }
        G[i] = (G[i - 1] + g[i]) % m;
        H[i] = 1;
        for (int j = 1; j < i - 1; ++j) {
            H[i] = (H[i] + (ll)g[j] * (i - j - 1)) % m;
        }
    }

    std::cout << (f[n] + m) % m << '\n';

    return 0;
}