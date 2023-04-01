#include <bits/stdc++.h>

using ll = long long int;

int n;
std::vector<int> ans;

bool dfs(int x){
	if(x % 2 == 0) return false;
	if(x == 1) return true;
	if(dfs((x + 1) / 2)){
		ans.push_back(1);
		return true;
	}
	if(dfs((x - 1) / 2)){
		ans.push_back(2);
		return true;
	}
	return false;
}

void solve(void){
	std::cin >> n;
	ans.clear();
	if(!dfs(n)) std::cout << "-1\n";
	else{
		std::cout << ans.size() << '\n';
		for(int i : ans) std::cout << i << ' ';
		std::cout << '\n';
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