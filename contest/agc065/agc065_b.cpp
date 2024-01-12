#include <bits/stdc++.h>

const int MAXN = 5e3 + 19, MOD = 1e9 + 7;

int n;
int p[MAXN], dp[MAXN][MAXN];

int main() {
    std::cin >> n;

    for (int i = 1; i <= n; ++i) {
        std::cin >> p[i];
    }

    p[0] = -1, dp[n + 1][n] = 1;
    for (int i = n; i >= 1; --i) {
        int s = 0;
        for (int j = n; j >= 0; --j) {
            s = (s + dp[i + 1][j]) % MOD;
            if (p[j] < i) {dp[i][j] = s;}
        }
    }

    std::cout << dp[1][0] << '\n';
}