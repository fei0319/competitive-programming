#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 5e5 + 19;

int n, suf[maxn];
std::pair<int, int> a[maxn];

void solve(void){
	std::cin >> n;
	for(int i = 1; i <= n; ++i)
		std::cin >> a[i].first >> a[i].second;
	std::sort(a + 1, a + 1 + n);
	std::set<int> seconds;
	
	suf[n + 1] = 0;
	for(int i = n; i >= 1; --i) suf[i] = std::max(suf[i + 1], a[i].second);
	
	int ans = 1e9;
	for(int i = 1; i <= n; ++i){
		int first = a[i].first, second = suf[i + 1];
		if(i > 1 && a[i].first == a[i - 1].first)
			seconds.insert(a[i].second);
		if(second <= first){
			auto it = seconds.lower_bound(first);
			if(it != seconds.end())
				ans = std::min(ans, *it - first);
			if(it != seconds.begin())
				ans = std::min(ans, first - std::max(second, *--it));
		}
		seconds.insert(a[i].second);
		if(i != n)
			ans = std::min(ans, second > first ? second - first : first - second);
	//	std::cout << ans << '\n';
	}
	std::cout << ans << '\n';
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