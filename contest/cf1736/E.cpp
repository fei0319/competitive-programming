#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 5e2 + 3;
const int INF = 1e9;

int n, a[MAXN], s[MAXN];
int dp[MAXN][MAXN];

void chkmax(auto &a, const auto &b) {
    if (a < b) {
        a = b;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = -INF;
        }
    }
    dp[0][1] = 0;

    for (int i = 1; i <= n; ++i) {
        std::vector<int> f(n + 1, -INF);
        for (int j = 0; j <= n; ++j) {

            std::vector<int> g(f);
            for (int k = 0; k <= n; ++k) {
                g[k] += a[i];
            }

            if (j < i) {
                for (int k = i - j - 1; k <= n; ++k) {
                    chkmax(g[k - (i - j - 1)], dp[j][k]);
                }
            }

            for (int k = 0; k < n; ++k) {
                chkmax(dp[j][k + 1], f[k] + a[i]);
            }
            f.swap(g);
        }
    }

    std::cout << *std::max_element(dp[n], dp[n] + n + 1) << '\n';

    return 0;
}