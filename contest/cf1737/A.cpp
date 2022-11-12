#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e5 + 19;

int n, k, cnt[maxn];
char s[maxn];

void solve(void){
	std::cin >> n >> k >> s + 1;
	for(int i = 1; i <= 25; ++i){
		cnt[i] = 0;
	}
	for(int i = 1; i <= n; ++i){
		++cnt[s[i] - 'a' + 1];
	}
	for(int i = 1; i <= k; ++i){
		int ptr = 0;
		while(cnt[ptr + 1] && ptr + 1 <= n / k){
			++ptr;
		}
		if(ptr){
			for(int j = 1; j <= ptr; ++j){
				--cnt[j];
			}
			std::cout << char('a' + ptr);
		}
		else{
			std::cout << 'a';
		}
	}
	std::cout << std::endl;
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