#include <bits/stdc++.h>

using ll = long long int;

void solve() {
	int n;
	std::cin >> n;
	
	if (n & 1) {
		std::cout << "NO\n";
		return;
	}
	
	std::cout << "YES\n";
	for (int i = 1; i <= n / 2; ++i) {
		if (i & 1) {
			std::cout << "AA";
		} else {
			std::cout << "BB";
		}
	}
	std::cout << '\n';
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