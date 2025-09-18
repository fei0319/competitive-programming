#include <iostream>
#include <iterator>
#include <vector>

using i64 = int64_t;

int qpow(int a, int b, int p) {
    int res = 1;
    while (b) {
        if (b & 1) res = (i64)res * a % p;
        a = (i64)a * a % p, b >>= 1;
    }
    return res;
}

void solve() {
    int n, x, p, m;
    std::cin >> n >> x >> p >> m;

    std::vector<int> a(m + 1);
    for (int &i : a) std::cin >> i;

    std::vector<std::vector<int>> S(m + 1);
    S[0] = std::vector<int>{1};
    for (int i = 1; i <= m; ++i) {
        S[i].resize(i + 1);
        for (int j = 0; j <= i; ++j) {
            S[i][j] = ((j - 1 >= 0 ? S[i - 1][j - 1] : 0) +
                       i64(j <= i - 1 ? S[i - 1][j] : 0) * j) %
                      p;
        }
    }

    std::vector<int> b(m + 1);
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= i; ++j) {
            b[j] = (b[j] + (i64)a[i] * S[i][j]) % p;
        }
    }

    int ans = 0;
    int f = 1;
    for (int t = 0; t <= m; ++t) {
        ans = (ans + (i64)f * b[t] % p * qpow(x + 1, n - t, p)) % p;
        f = (i64)f * (n - t) % p * x % p;
    }

    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();
}
