#include <bits/stdc++.h>

using ll = long long int;

int n, r1, c1, r2, c2, r3, c3, X, Y;

inline int rabs(int x){
	return x > 0 ? x : -x;
}

inline bool cor(int a, int b, int x, int y){
	return (a == x && rabs(b - y) == 1) || ((b == y) && rabs(a - x) == 1);
}

void solve(void){
	std::cin >> n >> r1 >> c1 >> r2 >> c2 >> r3 >> c3;
	std::cin >> X >> Y;
	int x = 0, y = 0;
	if(cor(r1, c1, r2, c2) && cor(r1, c1, r3, c3)){
		x = r1, y = c1;
	}
	if(cor(r2, c2, r1, c1) && cor(r2, c2, r3, c3)){
		x = r2, y = c2;
	}
	if(cor(r3, c3, r1, c1) && cor(r3, c3, r2, c2)){
		x = r3, y = c3;
	}
	if((x == 1 || x == n) && (y == 1 || y == n)){
		std::cout << ((X == x || Y == y) ? "YES" : "NO") << std::endl;
		return;
	}
	std::cout << ((rabs(X - x) % 2 == 1 && rabs(Y - y) % 2 == 1) ? "NO" : "YES") << std::endl;
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