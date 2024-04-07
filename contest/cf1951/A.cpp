#include <bits/stdc++.h>

using ll = long long int;

void solve() {
	int n;
	std::string s;
	std::cin >> n >> s;
	int tot = std::count(s.begin(), s.end(), '1');
	if (tot % 2 != 0) {
		std::cout << "NO\n";
		return;
	}
	
	bool has_adj = false;
	for (int i = 0; i + 1 < n; ++i) {
		if (s[i] == '1' && s[i + 1] == '1') {
			has_adj = true;
		}
	}
	if (tot == 2 && has_adj) {
		std::cout << "NO\n";
		return;
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