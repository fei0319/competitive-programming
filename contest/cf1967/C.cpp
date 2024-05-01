#include <bits/stdc++.h>

using ll = long long int;

constexpr int MAXN = 5e5 + 19, MOD = 998244353;

constexpr int qpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = (ll)res * a % MOD;
		a = (ll)a * a % MOD, b >>= 1;
	}
	return res;
}

int fact[MAXN], ifact[MAXN], inv[MAXN];
void init(const int N) {
	fact[0] = 1;
	for (int i = 1; i <= N; ++i) fact[i] = (ll)fact[i - 1] * i % MOD;
	ifact[N] = qpow(fact[N], MOD - 2);
	for (int i = N - 1; i >= 0; --i) ifact[i] = (ll)ifact[i + 1] * (i + 1) % MOD;
	
	for (int i = 1; i <= N; ++i) {
		inv[i] = (ll)fact[i - 1] * ifact[i] % MOD;
	}
}

int n, k, a[MAXN];

void solve(int l, int r) {
	if (l == r) return;
	int mid = (l + r) / 2;
	
	solve(l, mid);
	
	int len = mid - l + 1;
	for (int i = 1; i <= len; ++i) {
		int p = 0, b = 1;
		for (int x = i; x <= len * 2; x += x & -x) {
			int v = l - 1 + x;
			if (v > mid)
				a[v] = (a[v] - (ll)a[l - 1 + i] * b) % MOD;
			
			++p;
			b = (ll)b * (p + k - 1) % MOD;
			b = (ll)b * inv[p] % MOD;
		}
	}
	
	solve(mid + 1, r);
}

void solve() {
	std::cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
	}
	
	int N = 1;
	while (N < n) N *= 2;
	
	solve(1, N);
	for (int i = 1; i <= n; ++i) {
		std::cout << (a[i] + MOD) % MOD << ' ';
	}
	std::cout << '\n';
}

int main() {
	init(5e5);
	
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}