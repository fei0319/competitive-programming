#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 5e3 + 19, B = 8;
const int INF = 1e9;

int n, k;
int dp[MAXN][1 << B], p[MAXN], pos[MAXN];

void chkmin(auto &a, const auto &b) {
    if (a > b) {
        a = b;
    }
}

struct BIT {
    int tr[MAXN];
    void update(int x, int k) {
        for (; x <= n; x += x & -x) {
            tr[x] += k;
        }
    }
    int query(int x) {
        int res = 0;
        for (; x; x -= x & -x) {
            res += tr[x];
        }
        return res;
    }
} mt;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        std::cin >> p[i];
        pos[p[i]] = i;
    }

    for (int i = 1; i <= n + 1; ++i) {
        std::fill(dp[i], dp[i] + (1 << k), INF);
    }
    dp[1][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int S = 0; S < (1 << k); ++S) {
            int tot = i - 1;
            for (int j = 1; j <= k && i + j <= n; ++j) {
                if (S & (1 << (j - 1))) {
                    tot += 1;
                    mt.update(pos[i + j], 1);
                }
            }

            int nxt = 1;
            while (S & (1 << (nxt - 1))) {
                nxt += 1;
            }
            chkmin(dp[i + nxt][S >> nxt],
                   dp[i][S] + tot - mt.query(pos[i]));

            for (int j = 1; j <= k && i + j <= n; ++j) {
                if (!(S & (1 << (j - 1)))) {
                    chkmin(dp[i][S | (1 << (j - 1))],
                           dp[i][S] + tot - mt.query(pos[i + j]));
                }
            }

            for (int j = 1; j <= k && i + j <= n; ++j) {
                if (S & (1 << (j - 1))) {
                    tot += 1;
                    mt.update(pos[i + j], -1);
                }
            }
        }
        mt.update(pos[i], 1);
    }

    std::cout << dp[n + 1][0] << '\n';

    return 0;
}