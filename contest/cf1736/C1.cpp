#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

int n, a[maxn], s[maxn];

void solve(void){
	std::cin >> n;
	ll ans = 0ll;
	for(int i = 1; i <= n; ++i){
		std::cin >> a[i];
		s[i] = std::min(s[i - 1] + 1, a[i]);
		ans += s[i];
	}
	std::cout << ans << std::endl;
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