#include <bits/stdc++.h>

using ll = long long int;

int n, a[1000];

void solve(void){
	std::cin >> n;
	for(int i = 1; i <= n; ++i){
		std::cin >> a[i];
	}
	std::sort(a + 1, a + 1 + n);
	ll ans = 1e18;
	for(int i = 1; i <= n; ++i){
		if(i > 1 && i < n){
			ans = std::min(ans, ll(a[i + 1] - a[i - 1]));
		}
		if(i > 2){
			ans = std::min(ans, ll(a[i] - a[i - 1]) + (a[i] - a[i - 2]));
		}
		if(i < n - 1){
			ans = std::min(ans, ll(a[i + 1] - a[i]) + (a[i + 2] - a[i]));
		}
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