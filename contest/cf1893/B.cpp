#include <bits/stdc++.h>

using ll = long long int;

void solve(void) {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> a(n), b(m);
	for (int &i : a) {
		std::cin >> i;
	}
	for (int &i : b) {
		std::cin >> i;
	}
	
	std::sort(b.begin(), b.end(), std::greater<int>());
	int l = 0, r = b.size() - 1;
	int u = 0, v = a.size() - 1;
	std::vector<int> left, right;
	while (l <= r && u <= v) {
		while (l <= r && u <= v && b[l] > a[u]) {
			left.push_back(b[l++]);
		}
		left.push_back(a[u++]);
		while (l <= r && u <= v && b[r] < a[v]) {
			right.push_back(b[r--]);
		}
		if (u <= v) right.push_back(a[v--]);
	}
	while (u <= v) left.push_back(a[u++]);
	while (l <= r) left.push_back(b[l++]);
	
	std::reverse(right.begin(), right.end());
	
	for (int i : left) {
		std::cout << i << ' ';
	}
	for (int i : right) {
		std::cout << i << ' ';
	}
	
	std::cout << '\n';
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