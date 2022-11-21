#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e6 + 19;

int n, l, a[maxn];

void solve(void){
	std::cin >> n >> l;
	int sg = 0, hl = l;
	for(int i = 1; i <= n; ++i){
		std::cin >> a[i];
	}
	for(int i = 1; i <= n; ++i){
		if(hl >= a[i] + 1){
			hl -= a[i] + 1;
			++sg;
		}else{
			if(hl >= a[i]) hl -= a[i];
			else if(a[i] == 1 && sg) --sg;
			else{
				std::cout << "No\n";
				return;
			}
		}
	}
	std::cout << "Yes\n";
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