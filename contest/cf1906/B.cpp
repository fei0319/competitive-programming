#include <bits/stdc++.h>

using ll = long long int;

int f(std::vector<int> a) {
	int res = 0, n = a.size();
	for (int i = 0; i < n; ++i) {
		if (!a[i]) continue;
		if (i == res) {
			res += 1;
			continue;
		}
		if (i + 1 < n && a[i + 1]) {
			res += 2;
			a[i] = 0;
			a[i + 1] = 0;
		} else {
			res += 2;
			if (i + 1 < n)
				a[i + 1] ^= 1;
		}
	}
	return res;
}

void read(std::vector<int> &a) {
	std::string s;
	std::cin >> s;
	a.resize(s.size());
	for (int i = 0; i < (int)s.size(); ++i) {
		a[i] = (s[i] == '1');
	}
}

void solve(void) {
	int n;
	std::cin >> n;
	std::vector<int> a(n), b(n);
	read(a), read(b);
	if ((f(a) + 1) / 2 == (f(b) + 1) / 2) {
		std::cout << "YES\n";
	} else {
		std::cout << "NO\n";
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