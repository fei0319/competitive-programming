#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 2e2 + 4;

int n, k, a[MAXN];
bool vist[MAXN];
std::vector<std::pair<int, int>> s;
std::vector<int> ans[MAXN];

int dp[MAXN][MAXN][MAXN];
std::vector<int> solve(int v) {
    const int NA = -12314332;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= v; ++j) {
            for (int k = 0; k < v; ++k) {
                dp[i][j][k] = NA;
            }
        }
    }

    dp[0][0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < v; ++j) {
            for (int k = 0; k < v; ++k) {
                if (dp[i - 1][j][k] != NA) {
                    int p = dp[i - 1][j][k] >= 0 ? i - 1 : -dp[i - 1][j][k] - 1;

                    if (!vist[i])
                        dp[i][j + 1][(k + a[i]) % v] = p;
                    dp[i][j][k] = -p - 1;
                }
            }
        }
    }

    for (int i = v; i <= n; ++i) {
        if (dp[i][v][0] >= 0) {
            std::vector<int> res;
            int now = i, j = v, k = 0;
            while (now != 0) {
                res.push_back(a[now]);
                vist[now] = true;

                j -= 1, k = ((k - a[now]) % v + v) % v;
                now = dp[now][j + 1][(k + a[now]) % v];
            }

            return res;
        }
    }
    exit(-1);
}

int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }

    for (int i = 1; i <= k; ++i) {
        int t;
        std::cin >> t;
        s.emplace_back(t, i);
    }

    std::sort(s.begin(), s.end(), std::greater<>());

    for (int i = 1; i < k; ++i) {
        auto [v, id] = s.back();
        s.pop_back();
        ans[id] = std::move(solve(v));
    }

    auto [v, id] = s.back();
    int r = 0;
    for (int i = 1; i <= n; ++i) {
        if (!vist[i]) {
            ans[id].push_back(a[i]);
            r += a[i];
        }
    }
    r = (v - r) % v + v;
    ans[id].push_back(r);

    std::cout << r << '\n';
    for (int i = 1; i <= k; ++i) {
        for (int j : ans[i]) {
            std::cout << j << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}