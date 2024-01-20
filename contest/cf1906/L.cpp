#include <bits/stdc++.h>

int main(int argc, char *argv[]) {
	int n, k;
	std::cin >> n >> k;
	if (k < n / 2 || k == n) {
		std::cout << "-1\n";
		return 0;
	}
	
	std::string s;
	if (k % 2 == 1) {
		for (int i = 0; i < (k + 1) / 2; ++i) {
			s += "()";
		}
	} else if (k < n / 4 * 3) {
		for (int i = 0; i < n / 4; ++i) s += '(';
		for (int i = 0; i < k - n / 4 * 2; ++i) s += ')';
		for (int i = 0; i < n / 4; ++i) s += '(';
		if (n / 2 % 2 == 1) s += '(';
		while (s.size() < n) s.push_back(')');
	} else if (k % 4 != 0) {
		int p = (k / 2 - 1) / 2;
		s += "(()";
		for (int i = 0; i < p; ++i) s += ")(";
		for (int i = 0; i < p; ++i) s += "()"; 
		s += ")";
	} else {
		s += '(';
		for (int i = 0; i < k / 4; ++i) s += ")(";
		for (int i = 0; i < k / 4; ++i) s += "()";
		s += ')';
	}
	if (k == n / 2) s = "";
	
	int p = (n - s.size()) / 2;
	for (int i = 0; i < p; ++i) std::cout << '(';
	std::cout << s;
	for (int i = 0; i < p; ++i) std::cout << ')';
	
    return 0;
}