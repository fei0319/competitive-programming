#include <bits/stdc++.h>

using ll = long long int;

constexpr int mod = 1e9 + 7;

int qpow(int a, int b){
	int res = 1;
	while(b){
		if(b & 1) res = (ll)res * a % mod;
		a = (ll)a * a % mod, b >>= 1;
	}
	return res;
}

void solve(void){
	int n; std::cin >> n;
	int ans = (ll)n * (n + 1) % mod * (n + n + 1) % mod * qpow(3, mod - 2) % mod - (ll)n * (n + 1) % mod * qpow(2, mod - 2) % mod;
	ans = (ll)ans * 2022 % mod;
	std::cout << (ans + mod) % mod << std::endl;
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