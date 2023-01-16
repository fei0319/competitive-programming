#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

int n, a[maxn];

void solve(void){
	std::cin >> n;
	for(int i = 1; i <= n; ++i) std::cin >> a[i];
	std::sort(a + 1, a + 1 + n);
	
	int ans = (a[1] != 0);
	a[n + 1] = 1e9;
	for(int l = 1, r; l <= n; l = r + 1){
		r = l;
		while(r + 1 <= n && a[r + 1] == a[r]) ++r;
		if(r > a[r] && r < a[r + 1]) ++ans;//, std::cout << r << '\n';
	}
	std::cout << ans << '\n';
}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	int T;
	std::cin >> T;
	
	while(T--){
		solve();
	}
	
	return 0;
}