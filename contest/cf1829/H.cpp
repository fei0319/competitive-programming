#include <bits/stdc++.h>

using ll = long long int;

constexpr int MAXS = 1 << 6, MOD = 1e9 + 7;

int n, k;
int dp[MAXS], tmp[MAXS];

void solve(void) {
	std::cin >> n >> k;
	for (int i = 0; i < MAXS; ++i) {
		dp[i] = 0;
	}
	dp[MAXS - 1] = 1;
	for (int i = 1; i <= n; ++i) {
		int x;
		std::cin >> x;
		for (int s = 0; s < MAXS; ++s) {
			tmp[s] = dp[s];
		}
		for (int s = 0; s < MAXS; ++s) {
			dp[s & x] = (dp[s & x] + tmp[s]) % MOD;
		}
	}
	--dp[MAXS - 1];
	int ans = 0;
	for (int s = 0; s < MAXS; ++s) {
		if (__builtin_popcount(s) == k) {
			ans = (ans + dp[s]) % MOD;
		}
	}
	std::cout << (ans + MOD) % MOD << '\n';
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