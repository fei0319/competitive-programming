#include <bits/stdc++.h>

constexpr int maxn = 1e5 + 19;

int n, a[maxn];

void solve(void){
	std::vector<int> odd, even;
	
	std::cin >> n;
	for(int i = 1; i <= n; ++i){
		std::cin >> a[i];
		if(a[i] & 1){
			odd.push_back(i);
		}
		else{
			even.push_back(i);
		}
	}
	
	std::vector<std::pair<int, int>> ans;
	
	if(a[1] & 1){
		for(int i = odd.size() - 1; i >= 1; --i){
			ans.emplace_back(odd[i - 1], odd[i]);
		}
		for(int i : even){
			ans.emplace_back(1, i);
		}
	}
	else{
		for(int i = even.size() - 1; i >= 1; --i){
			ans.emplace_back(even[i - 1], even[i]);
		}
		for(int i : odd){
			ans.emplace_back(1, i);
		}
	}
	
	std::cout << ans.size() << std::endl;
	for(auto [x, y] : ans){
		std::cout << x << ' ' << y << '\n';
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