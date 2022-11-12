// Problem: A. Mainak and Array
// Contest: Codeforces Round #819 (Div. 1 + Div. 2) and Grimoire of Code Annual Contest 2022
// URL: https://codeforces.com/contest/1726/problem/A
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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

const int maxn = 2e3 + 19;

int n, a[maxn];

int main(){
	int T; read(T);
	while(T--){
		read(n);
		for(int i = 1; i <= n; ++i) read(a[i]);
		int ans = a[n] - a[1];
		for(int i = 2; i <= n; ++i) chkmax(ans, a[(n - 2 + i) % n + 1] - a[i]);
		int max = a[n], min = a[1];
		for(int i = 2; i < n; ++i) chkmax(max, a[i]), chkmin(min, a[i]);
		chkmax(ans, max - a[1]), chkmax(ans, a[n] - min);
		printf("%d\n", ans);
	}
}