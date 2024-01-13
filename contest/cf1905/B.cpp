#include <bits/stdc++.h>

using ll = long long int;

void solve(void) {
	int n;
	std::cin >> n;
	
	std::vector<int> deg(n);
	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		std::cin >> u >> v;
		++deg[u - 1], ++deg[v - 1];
	}
	
	int cnt = 0;
	for (int i : deg) {
		if (i == 1) {
			cnt += 1;
		}
	}
	
	std::cout << (cnt + 1) / 2 << '\n';
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