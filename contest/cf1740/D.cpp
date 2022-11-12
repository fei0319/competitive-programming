#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e6 + 19;

int n, m, k, a[maxn];

void solve(void){
	std::cin >> n >> m >> k;
	for(int i = 1; i <= k; ++i){
		std::cin >> a[i];
	}
	int cap = n * m - 3,
		rest = k;
//	std::cout << cap << '\n';
	std::priority_queue<int> q;
	for(int i = 1; i <= k; ++i){
		while(!q.empty() && q.top() == rest){
			--rest;
			q.pop();
		}
		if((int)q.size() == cap){
			std::cout << "TIDAK" << std::endl;
			return;
		}
		q.push(a[i]);
	}
	std::cout << "YA" << std::endl;
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