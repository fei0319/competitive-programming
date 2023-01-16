#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e5 + 19;

int n, a[maxn];

void solve(void){
	std::cin >> n;
	for(int i = 1; i <= n; ++i) std::cin >> a[i];
	std::sort(a + 1, a + 1 + n);
	std::reverse(a + 1, a + 1 + n);
	int fst = 0;
	for(int i = 2; i <= n; ++i)
		if(a[i] != a[1])
			fst = i;
	if(fst) std::swap(a[2], a[fst]);
	ll s = 0;
	for(int i = 1; i <= n; ++i){
		if(a[i] == s){
			std::cout << "NO\n";
			return;
		}
		s += a[i];
	}
	std::cout << "YES\n";
	for(int i = 1; i <= n; ++i) std::cout << a[i] << ' ';
	std::cout << '\n';
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