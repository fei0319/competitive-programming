#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e5 + 19;

int n, cnt[maxn];
char s[maxn];

void solve(void){
	std::cin >> n >> s + 1;
	int ans = 0;
	for(int r = 1; r <= n; ++r){
		for(int i = 0; i < 10; ++i){
			cnt[i] = 0;
		}
		int div = 0, max = 0;
		for(int l = r; l >= 1; --l){
			max = std::max(max, ++cnt[s[l] - '0']);
			if(cnt[s[l] - '0'] == 1){
				++div;
			}
			if(max > 10){
				break;
			}
			if(max <= div){
				++ans;
			}
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