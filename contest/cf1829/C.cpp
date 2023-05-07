#include <bits/stdc++.h>

using ll = long long int;

constexpr int MAXN = 2e5 + 19;

int n, m;
ll dp[4], nxt[4];
std::string s;

void solve(void) {
	std::cin >> n;
	for (int i = 0; i < 4; ++i) {
		dp[i] = 1e18;
	}
	dp[0] = 0;
	for (int i = 1; i <= n; ++i) {
		std::cin >> m >> s;
		int status = (s[0] - 48) + (s[1] - 48) * 2;
		for (int j = 0; j < 4; ++j) {
			nxt[j] = dp[j];
		}
		for (int j = 0; j < 4; ++j) {
			nxt[j | status] = std::min(nxt[j | status], dp[j] + m);
		}
		for (int j = 0; j < 4; ++j) {
			dp[j] = nxt[j];
		}
	}
	if (dp[3] == ll(1e18)) {
		std::cout << "-1\n";
	} else {
		std::cout << dp[3] << '\n';
	}
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