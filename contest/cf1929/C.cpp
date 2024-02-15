#include <bits/stdc++.h>

using ll = long long int;

void solve() {
	int k, x, a;
	std::cin >> k >> x >> a;
	
	ll s = 0;
	for (int i = 1; i <= x + 1; ++i) {
		ll y = s / (k - 1) + 1;
		if (s + y > a) {
			std::cout << "NO\n";
			return;
		}
		s += y;
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