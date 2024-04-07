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

constexpr int MAXN = 3e5 + 19;

int n, m;
int a[MAXN];

int f(int x) {
    int a = (ll)n * x % MOD;
    int b = ((ll)m * m - (ll)x * x) % MOD;
    return (ll)a * b % MOD * qpow(6LL * m % MOD, MOD - 2) % MOD;
}

void solve() {
	std::cin >> n >> m;

    int ans = 0;
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}

    std::sort(a, a + n);

    assert(f(m) == 0);

    for (int i = 0; i < n; ++i) {
        ans = (ans + f((a[(i + 1) % n] - a[i] + m) % m)) % MOD;
    }
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