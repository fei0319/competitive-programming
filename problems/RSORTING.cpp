#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e3 + 19;

int n, a[maxn], b[maxn];
int tr[maxn];

void solve(void){
	std::cin >> n;
	for(int i = 1; i <= n; ++i) std::cin >> a[i];
	
	for(int i = 1; i <= n; ++i) b[i] = i;
	std::sort(b + 1, b + 1 + n, [](const int &x, const int &y){
		return a[x] < a[y];
	});
	for(int i = 1; i <= n; ++i) a[b[i]] = i;
	for(int i = 1; i <= n; ++i) tr[i] = 0;
	
	
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