#include <bits/stdc++.h>

using ll = long long int;

int n, m;

void solve(void) {
	std::cin >> n >> m;
	std::vector<int> now{n}, tmp;
	while (!now.empty()) {
		tmp.clear();
		for (int i : now) {
			if (i == m) {
				std::cout << "YES\n";
				return;
			}
			if (i < m) {
				continue;
			}
			if (i % 3 == 0) {
				tmp.push_back(i / 3);
				tmp.push_back(i / 3 * 2);
			}
		}
		now.swap(tmp);
	}
	std::cout << "NO\n";
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