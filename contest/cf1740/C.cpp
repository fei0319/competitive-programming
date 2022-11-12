#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

int n, a[maxn];

void solve(void){
	std::cin >> n;
	for(int i = 1; i <= n; ++i){
		std::cin >> a[i];
	}
	std::sort(a + 1, a + 1 + n);
	ll ans = a[n] - a[1];
	for(int i = 3; i <= n; ++i){
		ans = std::max(ans, ll(a[i] - a[i - 1]) + ll(a[i] - a[1]));
	}
	for(int i = n - 2; i >= 1; --i){
		ans = std::max(ans, ll(a[i + 1] - a[i]) + ll(a[n] - a[i]));
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