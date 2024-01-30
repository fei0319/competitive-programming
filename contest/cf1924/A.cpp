#include <bits/stdc++.h>

using ll = long long int;
const int INF = 1e9;

void solve() {
    int n, k, m;
    std::string s;

    std::cin >> n >> k >> m;
    std::cin >> s;
    s = " " + s;

    std::vector<int> dp(m + 1, INF);
    std::vector<int> prev(m + 1, INF);
    std::vector<int> has(27);
    dp[0] = 0, prev[0] = 0;
    for (int i = 1; i <= m; ++i) {
        if (s[i] - 'a' + 1 <= k) {
            for (int j = i - 1; j >= 0; --j) {
                if (dp[j] + 1 < dp[i]) {
                    dp[i] = dp[j] + 1;
                    prev[i] = j;
                }
                if (s[j] == s[i]) {
                    break;
                }
            }
        }
    }

    std::function<void(int)> output = [&](int x) {
        if (x == 0) return;
        output(prev[x]);
        std::cout << s[x];
    };

    for (int i = m; i >= 0; --i) {
        if (dp[i] < n) {
            for (int j = 1; j <= k; ++j) {
                if (!has[j]) {
                    std::cout << "NO\n";
                    output(i);
                    for (int p = 0; p < n - dp[i]; ++p) {
                        std::cout << char('a' + j - 1);
                    }
                    std::cout << '\n';
                    return;
                }
            }
        }

		if (i) {
        	has[s[i] - 'a' + 1] = true;
        }
    }
    std::cout << "YES\n";
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