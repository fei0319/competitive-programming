#include <bits/stdc++.h>

using ll = long long int;

void solve(void){
	int n;
	std::cin >> n;
	ll ans = 1;
	for(int i = 1; i <= n; ++i){
		ll t; std::cin >> t;
		ans *= t;
	}
	std::cout << (ans + n - 1) * 2022 << '\n';
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