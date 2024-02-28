#include <bits/stdc++.h>
#include "atcoder/convolution"
#include "atcoder/modint"

using mint = atcoder::modint998244353;
using ll = long long int;

const int MAXN = 2e5 + 19;
const int MOD = 998244353;

constexpr int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = (ll)res * a % MOD;
        }
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}

int n, m, c[MAXN];
mint f[MAXN], fact[MAXN], p[MAXN];

std::vector<int> solve(const std::vector<std::vector<int>> &F, int l, int r) {
    if (l == r) {
        return F[l];
    }
    int mid = (l + r) /2 ;
    return atcoder::convolution(solve(F, l, mid), solve(F, mid + 1, r));
}

mint binom(int n, int m) {
    return fact[n] / (fact[n - m] * fact[m]);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        std::cin >> c[i];
    }

    fact[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fact[i] = fact[i - 1] * i;
    }

    std::vector<std::vector<int>> F;
    for (int i = 1; i <= m; ++i) {
        std::vector<int> Z(c[i] + 1);
        for (int j = 1; j <= c[i]; ++j) {
            Z[j] = binom(c[i], j).val();
        }
        F.push_back(std::move(Z));
    }

    std::vector<int> Z = solve(F, 0, F.size() - 1);

    f[0] = 1;
    for (int i = 1; i < n; ++i) {
        f[i] = mint(n) / (n - i);
    }

    mint ans = 0, s = 0;
    for (int i = 1; i <= n; ++i) {
        p[i] = Z[i] * fact[i] / (fact[n] / fact[n - i]);
    }

    for (int i = 1; i <= n; ++i) {
        s += f[i - 1];
        ans += s * (p[i] - p[i - 1]);
    }

    std::cout << ans.val() << '\n';

    return 0;
}