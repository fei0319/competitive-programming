#include <bits/stdc++.h>

using ll = long long int;

ll dp[70][2][2][2];
ll n, m;
bool ok[70];

inline int g(int a) {
    return a & 1;
}

void tran(int b, int less, int eq, int jw) {
    for (int i = 0; i <= 1; ++i) {
        dp[b + 1][(less && i <= g(m >> (b + 1))) || i < g(m >> (b + 1))]
          [eq ^ (i ^ (jw ^ i ^ g(n >> (b + 1))))]
          [jw + i + g(n >> (b + 1)) >= 2] += dp[b][less][eq][jw];
    }
}

void init() {
    int b = -1, less = 0, eq = 1, jw = 0;
    for (int i = 0; i <= 1; ++i) {
        dp[b + 1][(less && i <= g(m >> (b + 1))) || i < g(m >> (b + 1))]
          [eq ^ (i ^ (jw ^ i ^ g(n >> (b + 1))))]
          [jw + i + g(n >> (b + 1)) >= 2]++;
    }
}

void solve(void) {
    std::cin >> n >> m;
    ok[62] = 0;
    for (int i = 61; i >= 0; --i) {
        if (!g(n >> i)) {
            ok[i] = 0;
        } else if (!g(n >> (i + 1))) {
            ok[i] = 0;
        } else {
            ok[i] = ok[i + 1] ^ 1;
        }
    }
    for (int i = 0; i <= 61; ++i) {
        for (int a = 0; a <= 1; ++a) {
            for (int b = 0; b <= 1; ++b) {
                for (int c = 0; c <= 1; ++c) {
                    dp[i][a][b][c] = 0;
                }
            }
        }
    }
    init();
    for (int i = 0; i <= 60; ++i) {
        for (int a = 0; a <= 1; ++a) {
            for (int b = 0; b <= 1; ++b) {
                for (int c = 0; c <= 1; ++c) {
                    tran(i, a, b, c);
                    //			std::cout << "dp_" << i << "_" << a << b << c
                    //<<
                    //"="
                    //<< dp[i][a][b][c] << std::endl;
                }
            }
        }
    }
    std::cout << dp[61][1][0][0] + dp[61][1][0][1] << std::endl;
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