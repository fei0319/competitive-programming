#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 5e2 + 19, maxm = 250000 + 19;

int n, m;
int u[maxm], v[maxm], w[maxm];
ll d[maxn][maxn];

void solve(void){
	std::cin >> n >> m;
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= n; ++j){
			d[i][j] = (i == j ? 0 : 1e18);
		}
	}
	for(int i = 1; i <= m; ++i){
		std::cin >> u[i] >> v[i] >> w[i];
		d[u[i]][v[i]] = d[v[i]][u[i]] = 1;
	}
	for(int k = 1; k <= n; ++k){
		for(int i = 1; i <= n; ++i){
			for(int j = 1; j <= n; ++j){
				if(d[i][k] + d[k][j] < d[i][j]){
					d[i][j] = d[i][k] + d[k][j];
				}
			}
		}
	}
	ll ans = 1e18;
	for(int i = 1; i <= m; ++i){
		ans = std::min(ans, (d[1][u[i]] + d[v[i]][n] + 1) * w[i]);
		ans = std::min(ans, (d[1][v[i]] + d[u[i]][n] + 1) * w[i]);
		for(int j = 1; j <= n; ++j){
			ans = std::min(ans, (d[1][j] + d[j][n] + d[u[i]][j] + 2) * w[i]);
			ans = std::min(ans, (d[1][j] + d[j][n] + d[v[i]][j] + 2) * w[i]);
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