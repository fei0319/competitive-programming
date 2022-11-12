#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

int n, k, h[maxn];
std::vector<std::pair<ll, ll>> a, b;

void solve(void){
	std::cin >> n >> k;
	for(int i = 1; i <= n; ++i){
		std::cin >> h[i];
	}
	a.clear(), b.clear();
	for(int i = k + 1; i <= n; ++i){
		int r = i;
		ll s = h[r], min = std::min(s, 0ll);
		while(r + 1 <= n && s < 0ll){
			s += h[++r];
			min = std::min(min, s);
		}
		a.emplace_back(s, min);
		i = r;
	}
	for(int i = k - 1; i >= 1; --i){
		int r = i;
		ll s = h[r], min = std::min(s, 0ll);
		while(r - 1 >= 1 && s < 0ll){
			s += h[--r];
			min = std::min(min, s);
		}
		b.emplace_back(s, min);
		i = r;
	}
	std::reverse(a.begin(), a.end());
	std::reverse(b.begin(), b.end());
	ll now = h[k];
	while(!a.empty() && !b.empty()){
		if(now + a.back().second >= 0){
			now += a.back().first;
			a.pop_back();
		}else if(now + b.back().second >= 0){
			now += b.back().first;
			b.pop_back();
		}else{
			break;
		}
	}
	std::cout << (a.empty() || b.empty() ? "YES" : "NO") << std::endl;
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