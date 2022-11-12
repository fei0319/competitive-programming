#include <bits/stdc++.h>

using ll = long long int;

int l, r;

bool judge(int l, int r){
	if(l == 0){
		return true;
	}
	for(int i = 30; i >= 0; --i){
		if((l & (1 << i)) != (r & (1 << i))){
			l &= ((1 << i) - 1);
			r &= ((1 << i) - 1);
			return r >= l;
		}
	}
	return true;
}

void solve(void){
	std::cin >> l >> r;
	std::cout << (judge(l, r) ? "Yes" : "No") << std::endl;
}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	int T;
	T = 1;
	
	while(T--){
		solve();
	}
	
	return 0;
}