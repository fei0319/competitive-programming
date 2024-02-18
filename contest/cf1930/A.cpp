#include <bits/stdc++.h>

using ll = long long int;

void solve() {
	int n;
	std::cin >> n;
	
	std::vector<int> a(n * 2);
	for (int i = 0; i < n * 2; ++i) {
		std::cin >> a[i];
	}
	std::sort(a.begin(), a.end());
	
	ll ans = 0;
	for (int i = 0; i < n; ++i) {
		ans += a[i * 2];
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