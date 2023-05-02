#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 3e5 + 19;

int n, a[maxn];

void solve(void){
	std::cin >> n;
	for(int i = 1; i <= n; ++i){
		std::cin >> a[i];
	}
	for(int i = n; i >= 1; --i) a[i] -= a[i - 1];
	ll sum = 0;
	for(int i = 2; i <= n; i += 2)
		sum += a[i];
	if(sum >= 0 || n % 2 == 1) std::cout << "YES\n";
	else std::cout << "NO\n";
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