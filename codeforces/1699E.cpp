#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 5e6 + 19;
const int INF = 1e9;

int n, m;
int dp[MAXN];
bool vist[MAXN];

void solve() {
    std::cin >> n >> m;

    std::multiset<int> s;
    std::fill(vist + 1, vist + 1 + m, false);
    for (int i = 1; i <= n; ++i) {
        int t;
        std::cin >> t;
        vist[t] = true;
    }

    for (int i = 1; i <= m; ++i) {
        if (vist[i]) {
            s.insert(i);
        }
    }

    int ans = INF;
    std::iota(dp + 1, dp + 1 + m, 1);
    for (int i = m; i >= 1; --i) {
        for (int j = i; (ll)i * j <= m; ++j) {
            if (dp[i * j] > dp[j]) {
                if (vist[i * j]) {
                    s.erase(s.find(dp[i * j]));
                }
                dp[i * j] = dp[j];
                if (vist[i * j]) {
                    s.insert(dp[i * j]);
                }
            }
        }
        if (*s.begin() >= i) {
            ans = std::min(ans, *--s.end() - i);
        }
    }

    std::cout << ans << '\n';
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