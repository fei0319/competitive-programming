#include <bits/stdc++.h>

using ll = long long int;

void solve(void){
	int n, a, b;
	std::cin >> n >> a >> b;
	if(a == n && b == n){
		std::cout << "Yes\n";
	}else if(a + b + 2 <= n){
		std::cout << "Yes\n";
	}else{
		std::cout << "No\n";
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