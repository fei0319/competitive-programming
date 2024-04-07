#include <bits/stdc++.h>

using ll = long long int;

int check(std::vector<int> a, int k) {
	int ans = 0;
	int n = a.size();
	
	if (k != 0) {
		++ans;
	}
	
	for (int i = k + 1; i < n; ++i) {
		if (a[k] > a[i]) {
			++ans;
		} else {
			break;
		}
	}
	return ans;
}

void solve() {
	int n, k;
	std::vector<int> a;
	
	std::cin >> n >> k;
	a.resize(n);
	for (int &i : a) {
		std::cin >> i;
	}
	
	--k;
	std::swap(a[k], a[0]);
	int ans = check(a, 0);
	std::swap(a[k], a[0]);
	
	for (int i = 0; i < n; ++i) {
		if (a[i] > a[k] && i < k) {
			std::swap(a[k], a[i]);
			ans = std::max(ans, check(a, i));
			break;
		}
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