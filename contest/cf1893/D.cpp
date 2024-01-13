#include <bits/stdc++.h>

using ll = long long int;

void solve(void) {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> cnt(n), s(m), d(m);
	for (int i = 0; i < n; ++i) {
		int c;
		std::cin >> c;
		++cnt[c - 1];
	}
	
	std::set<std::pair<int, int>> mt;
	for (int i = 0; i < n; ++i) {
		if (cnt[i])
			mt.emplace(cnt[i], i);
	}
	
	for (int &i : s) {
		std::cin >> i;
	}
	for (int &i : d) {
		std::cin >> i;
	}
	
	auto top = [&mt](int t) {
		std::vector<int> res;
		auto it = mt.end();
		while (it != mt.begin() && t) {
			--it, --t;
			res.push_back(it->second);
		}
		if (t) {
			return std::vector<int>();
		}
		return res;
	};
	auto take = [&mt, &cnt](int x) {
		mt.erase(std::make_pair(cnt[x]--, x));
		if (cnt[x])
			mt.insert(std::make_pair(cnt[x], x));
	};
	
	std::vector<std::vector<int>> a(m);
	for (int i = 0; i < m; ++i) {
		int sz = s[i];
		a[i].resize(sz);
		
		while (sz) {
			auto to_take = top(std::min(sz, d[i]));
			if (to_take.empty()) {
				std::cout << "-1\n";
				return;
			}
			for (int x : to_take) {
				take(x);
				a[i][--sz] = x;
			}
		}
	}
	
	for (auto &i : a) {
		for (int j : i) {
			std::cout << j + 1 << ' ';
		}
		std::cout << '\n';
	}
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