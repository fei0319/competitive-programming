// Problem: A. Make it Increasing
// Contest: Codeforces Round #783 (Div. 1)
// URL: https://codeforces.com/contest/1667/problem/A
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
typedef long long int ll;
template <typename Tp> void chkmax(Tp &a, const Tp &b){ a = std::max(a, b); }
template <typename Tp> void chkmin(Tp &a, const Tp &b){ a = std::min(a, b); }
template <typename Tp> void read(Tp &res){
	static char ch; ch = getchar(), res = 0;
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) res = res * 10 + ch - 48, ch = getchar();
}

const int maxn = 5e3 + 19;

int n, a[maxn];
ll b[maxn];

ll prev(int x){
	ll res = 0;
	b[x] = 0;
	for(int i = x - 1; i >= 1; --i){
		ll c = b[i + 1] / a[i] + 1;
		res += c, b[i] = c * a[i];
	}
	return res;
}

ll next(int x){
	ll res = 0;
	b[x - 1] = 0;
	for(int i = x; i <= n; ++i){
		ll c = b[i - 1] / a[i] + 1;
		res += c, b[i] = c * a[i];
	}
	return res;
}

int main(){
	read(n);
	for(int i = 1; i <= n; ++i) read(a[i]);
	ll ans = 1e18;
	for(int i = 1; i <= n + 1; ++i)
		chkmin(ans, prev(i - 1) + next(i));
	printf("%lld\n", ans);
}