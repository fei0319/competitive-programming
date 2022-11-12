// Problem: P5202 [USACO19JAN]Redistricting P
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5202
// Memory Limit: 125 MB
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

const int maxn = 3e5 + 19;

int n, k;
int dp[maxn], s[maxn];
char grass[maxn];
int q[maxn], h, t;

int main(){
	read(n), read(k);
	std::scanf("%s", grass + 1);
	for(int i = 1; i <= n; ++i) s[i] = s[i - 1] + (grass[i] == 'G' ? 1 : -1);
	q[h = t = 0] = 0;
	for(int i = 1; i <= n; ++i){
		while(i - q[h] > k) ++h;
		dp[i] = dp[q[h]] + (s[i] - s[q[h]] >= 0);
		while(h <= t && (dp[q[t]] > dp[i] || (dp[q[t]] == dp[i] && s[q[t]] <= s[i]))) --t;
		q[++t] = i;
	}
	printf("%d\n", dp[n]);
}