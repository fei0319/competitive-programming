#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e6 + 19;

int n;
char s[maxn];
bool vist[maxn];

void solve(void){
	std::cin >> n;
	std::cin >> s + 1;
	for(int i = 1; i <= n; ++i){
		if(s[i] == '0'){
			vist[i] = 1;
		}else{
			vist[i] = 0;
		}
	}
	ll ans = 0ll;
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i)
			if(vist[j]){
				ans += i;
				vist[j] = 0;
			}else if(s[j] == '1'){
				break;
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