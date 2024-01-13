#include <bits/stdc++.h>

using ll = long long int;

void solve(void) {
	int n;
	std::string s;
	std::cin >> n >> s;
	
	std::vector<std::vector<int>> pos(26);
	for (int i = 0; i < n; ++i) {
		pos[s[i] - 'a'].push_back(i);
	}
	for (int i = 0; i < 26; ++i) {
		std::reverse(pos[i].begin(), pos[i].end());
	}
	
	std::vector<int> t;
	for (int now = -1, c = 25; c >= 0; ) {
		while (c >= 0 && (pos[c].empty() || pos[c].back() <= now)) {
			while (!pos[c].empty() && pos[c].back() <= now) {
				pos[c].pop_back();
			}
			if (pos[c].empty()) c -= 1;
		}
		if (c >= 0) {
			now = pos[c].back();
			t.push_back(now);
		}
	}
	
	int cnt = 0;
	while (cnt < t.size() && s[t[cnt]] == s[t[0]]) {
		cnt += 1;
	}
	
	int d = t.size() - cnt;
	char max = s[t[0]];
	std::string x(d, ' ');
	for (int i = 0; i < d; ++i) {
		x[i] = s[t[t.size() - i - 1]];
	}
	for (int i = 0; i < d; ++i) {
		s[t[i]] = x[i];
	}
	for (int i = d; i < t.size(); ++i) {
		s[t[i]] = max;
	}
	
	auto is_sorted = [](const std::string s) {
		for (int i = 1; i < s.size(); ++i) {
			if (s[i] < s[i - 1]) {
				return false;
			}
		}
		return true;
	};
	if (is_sorted(s)) {
		std::cout << t.size() - cnt << '\n';
	} else {
		std::cout << "-1\n";
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