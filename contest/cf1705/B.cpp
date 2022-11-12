// Problem: B. Mark the Dust Sweeper
// Contest: Codeforces - Codeforces Round #807 (Div. 2)
// URL: https://codeforces.com/contest/1705/problem/B
// Memory Limit: 256 MB
// Time Limit: 1500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <cstring>
#include <cstdio>
#include <cctype>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>

typedef long long int ll;

template <typename Tp>
void chkmax(Tp &a, const Tp &b){ a = std::max(a, b); }
template <typename Tp>
void chkmin(Tp &a, const Tp &b){ a = std::min(a, b); }

template <typename Tp>
void read(Tp &res){
	static char ch; ch = getchar(), res = 0;
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) res = res * 10 + ch - 48, ch = getchar();
}

const int maxn = 2e5 + 19;

int T;
int n, a[maxn];

void solve(){
	read(n);
	for(int i = 1; i <= n; ++i) read(a[i]);
	int l = 1;
	ll ans = 0;
	while(l < n && a[l] == 0) ++l;
	for(int i = l; i < n; ++i)
		if(a[i]) ans += a[i];
		else ++ans;
	printf("%lld\n", ans);
}

int main(){
	read(T);
	while(T--) solve();
}

/*





















*/