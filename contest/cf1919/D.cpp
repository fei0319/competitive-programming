#include <bits/stdc++.h>

using ll = long long int;

struct Node {
	int l, r, val;
};

void solve(void) {
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (int &i : a) {
		std::cin >> i;
	}
	
	std::vector<Node> nodes(n + 1);
	std::vector<std::vector<int>> pos(n);
	
	nodes[n].val = -10;
	for (int i = 0; i < n; ++i) {
		
		nodes[i].l = i ? i - 1 : n;
		nodes[i].r = i + 1;
		
		nodes[i].val = a[i];
		
		pos[a[i]].push_back(i);
	}
	
	if (pos[0].size() != 1) {
		std::cout << "NO\n";
		return;
	}
	
	for (int i = n - 1; i >= 1; --i) {
		for (int j : pos[i]) {
			int l = nodes[j].l, r = nodes[j].r;
			if (nodes[l].val == i - 1 || nodes[r].val == i - 1 || nodes[r].val == i) {
				nodes[l].r = r;
				nodes[r].l = l;
			} else {
				std::cout << "NO\n";
				return;
			}
		}
	}
	
	std::cout << "YES\n";
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