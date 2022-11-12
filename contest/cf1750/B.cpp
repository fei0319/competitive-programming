#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

int n;
char s[maxn];

void solve(void){
	std::cin >> n;
	std::cin >> s + 1;
	int cnt[] = {0, 0};
	for(int i = 1; i <= n; ++i) ++cnt[s[i] - '0'];
	ll ans = (ll)cnt[0] * cnt[1];
	for(int l = 1, r; l <= n; l = r + 1){
		r = l;
		while(r + 1 <= n && s[r + 1] == s[r]) ++r;
		ans = std::max(ans, (ll)(r - l + 1) * (r - l + 1));
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