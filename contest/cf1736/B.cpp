#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e5 + 19;

int gcd(int a, int b){
	return b ? gcd(b, a % b) : a;
}

int lcm(int x, int y){
	return x * y / gcd(x, y);
}

int n, a[maxn], b[maxn];

void solve(void){
	std::cin >> n;
	for(int i = 1; i <= n; ++i){
		std::cin >> a[i];
	}
	a[0] = a[1], a[n + 1] = a[n];
	for(int i = 1; i <= n + 1; ++i){
		b[i] = lcm(a[i - 1], a[i]);
	}
	for(int i = 1; i <= n; ++i){
		if(gcd(b[i], b[i + 1]) != a[i]){
			std::cout << "NO\n";
			return;
		}
	}
	std::cout << "YES\n";
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