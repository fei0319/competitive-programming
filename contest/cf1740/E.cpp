#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e5 + 19;

std::vector<int> G[maxn];
int n, f[maxn], g[maxn];

void dfs(int node, int fa){
	f[node] = 1;
	for(int to : G[node]){
		if(to == fa) continue;
		dfs(to, node);
		g[node] += std::max(g[to], f[to]), f[node] = std::max(f[node], f[to] + 1);
	}
}

void solve(void){
	std::cin >> n;
	for(int i = 2, p; i <= n; ++i){
		std::cin >> p;
		G[p].push_back(i);
	}
	dfs(1, 0);
//	for(int i = 1; i <= n; ++i){
//		std::cout << i << ' ' << f[i] << ' ' << g[i] << '\n';
//	}
	std::cout << std::max(f[1], g[1]) << std::endl;
}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	int T = 1;
	
	while(T--){
		solve();
	}
	
	return 0;
}