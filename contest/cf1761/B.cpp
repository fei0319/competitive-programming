#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e6 + 19;

int n, a[maxn];

void solve(void){
	std::cin >> n;
	std::vector<int> tmp;
	for(int i = 1; i <= n; ++i){
		std::cin >> a[i];
		tmp.push_back(a[i]);
	}
	std::sort(tmp.begin(), tmp.end());
	tmp.resize(std::unique(tmp.begin(), tmp.end()) - tmp.begin());
	if(n == 1){
		std::cout << "1\n";
	}else if(tmp.size() == 2ll){
		std::cout << n / 2 + 1 << '\n';
	}else{
		std::cout << n << '\n';
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