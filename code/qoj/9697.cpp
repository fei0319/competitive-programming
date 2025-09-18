#include <bits/stdc++.h>

using i64 = int64_t;

int qpow(int a, int b, int p) {
    int res = 1;
    while (b) {
        if (b & 1) res = (i64)res * a % p;
        a = (i64)a * a % p, b >>= 1;
    }
    return res;
}

int main() {
    int n, k, M;
    std::cin >> n >> k >> M;

    std::vector<std::vector<int>> S2(k + 2);
    S2[0] = std::vector<int>{1};
    for (int i = 1; i <= k + 1; ++i) {
        S2[i].resize(i + 1);
        for (int j = 0; j <= i; ++j) {
            S2[i][j] = ((j - 1 >= 0 ? S2[i - 1][j - 1] : 0) +
                        (j <= i - 1 ? (i64)S2[i - 1][j] * j : 0)) %
                       M;
        }
    }

    std::vector<int> inv(n + k + 1);
    for (int i = 1; i <= n + k; ++i) inv[i] = qpow(i, M - 2, M);

    for (int x = 1; x <= n; ++x) {
        int ans = 0, f = 1;
        for (int i = 0; i <= k; ++i) {
            ans = (ans + (i64)f * S2[k + 1][i + 1]) % M;
            f = (i64)f * inv[x + i] % M * (i + 1) % M * (n - x - i) % M;
        }
        std::cout << ans << ' ';
    }
}
