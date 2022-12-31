#include <bits/stdc++.h>

using ll = long long int;

void solve(void){
	int n; std::cin >> n;
	if(n & 1){
		for(int i = 1; i <= n; ++i) std::cout << 1 << ' ';
		std::cout << '\n';
	}else{
		for(int i = 1; i <= n - 2; ++i) std::cout << 2 << ' ';
		std::cout << "1 3\n";
	}
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