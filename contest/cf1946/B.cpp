#include <bits/stdc++.h>

using ll = long long int;

constexpr int MOD = 1e9 + 7;

constexpr int qpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) {
			res = (ll)res * a % MOD;
		}
		a = (ll)a * a % MOD, b >>= 1;
	}
	return res;
}

void solve() {
	int n, k;
	std::cin >> n >> k;
	
	std::vector<int> a(n);
	for (int &i : a) {
		std::cin >> i;
	}
	
	using ll = long long int;
	ll min = 0, sum = 0, max = 0;
	for (int i = 0; i < n; ++i) {
		sum += a[i];
		max = std::max(max, sum - min);
		min = std::min(min, sum);
	}
	
	int ans = (sum - max + max % MOD * qpow(2, k)) % MOD;
	ans = (ans + MOD) % MOD;
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