#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

int n, fa[maxn], sz[maxn];
std::vector<int> G[maxn];

int getf(int node){
	return fa[node] == node ? node : fa[node] = getf(fa[node]);
}

void solve(void){
	std::cin >> n;
	for(int i = 1; i <= n; ++i){
		G[i].clear();
		fa[i] = i, sz[i] = 1;
	}
	for(int i = 2; i <= n; ++i){
		int x, y;
		std::cin >> x >> y;
		if(x < y){
			std::swap(x, y);
		}
		G[x].push_back(y);
	}
	int ans = 0;
	for(int i = 1; i <= n; ++i){
		int cnt = 0;
		for(int to : G[i]){
			int a = getf(i), b = getf(to);
			if(sz[b]){
				++cnt;
			}
			fa[b] = a, sz[a] += sz[b];
		}
		if(cnt >= 2){
			sz[getf(i)] -= 3;
			++ans;
		}
	}
	std::cout << ans << std::endl;
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