#include <bits/stdc++.h>

using ll = long long int;

int h(int x) {
    return (x + 1) / 2;
}

ll g(int n) {
    ll res = 0;
    for (int i = 1; i <= n; ++i) {
        res += (ll)i * h(n + 1 - i);
    }
    return res;
}

void solve() {
    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    ll ans = 0;
    
    std::vector<int> f{0, 0, 0};
    for (int i = 0; i < n; ++i) {
    	std::vector<int> g{0, 0, 0};
    	if (s[i] == '0') {
    		g[0] = f[0] + f[1] + 1;
    		g[1] = f[2];
    	} else {
    		ans += ll(f[0] + 1) * (n - i);
    		
    		g[0] = f[1];
    		g[1] = f[2];
    		g[2] = f[0] + 1;
    	}
    	f.swap(g);
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