#include <bits/stdc++.h>

using ll = long long int;

void solve() {
	int n, k;
	std::cin >> n >> k;
	
	const int M = 25;
	const int N = 1e9;
	
	std::vector<int> a;
	for (int i = 1; i * 2 - 1 < k; i *= 2) {
		a.push_back(i);
	}
	if (!a.empty()) {
		int v = k - 1 - (a.back() * 2 - 1);
		if (v) a.push_back(v);
	}
	
	a.push_back(k + 1);
	int now = k + 1, p = 0;
	while (a.size() < M && (now + ((ll)k << p)) <= N) {
		a.push_back(now + (k << p));
		++p;
	}
	
	std::cout << a.size() << '\n';
	for (int i : a) std::cout << i << ' ';
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