#include <bits/stdc++.h>

using ll = long long int;

void solve(void) {
    int n;
    std::string s;
    std::cin >> n >> s;

    std::vector<int> sum(n);
    sum[0] = (s[0] == '+' ? 1 : -1);
    for (int i = 1; i < n; ++i) {
        sum[i] = sum[i - 1] + (s[i] == '+' ? 1 : -1);
    }

    std::vector<int> mt(n * 2 + 1, -1);

    std::vector<int> dp(n);
    for (int i = 0; i < n; ++i) {
        if (i)
            dp[i] = dp[i - 1];
        dp[i] += 1;
        if (sum[i] == 0)
            dp[i] = 0;
        else if (mt[sum[i] + n] != -1) {
            dp[i] = dp[mt[sum[i] + n]];
        } else {
            mt[sum[i] + n] = i;
        }
    }

    std::cout << dp[n - 1] << '\n';
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}