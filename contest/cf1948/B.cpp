#include <bits/stdc++.h>

using ll = long long int;

void solve() {
	int n;
	std::cin >> n;
	
	std::vector<int> a(n);
	for (int &i : a) {
		std::cin >> i;
	}
		
	for (int i = -1; i < n; ++i) {
		std::vector<int> b;
		for (int j = 0; j <= i; ++j) {
			if (a[j] > 9) {
				b.push_back(a[j] / 10);
				b.push_back(a[j] % 10);
			} else {
				b.push_back(a[j]);
			}
		}
		for (int j = i + 1; j < n; ++j) {
			b.push_back(a[j]);
		}
		if (std::is_sorted(b.begin(), b.end())) {
			std::cout << "YES\n";
			return;
		}
	}
	
	std::cout << "NO\n";
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