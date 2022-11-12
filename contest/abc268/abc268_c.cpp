// Problem: C - Chinese Restaurant
// Contest: AtCoder - UNIQUE VISION Programming Contest 2022 Summer (AtCoder Beginner Contest 268)
// URL: https://atcoder.jp/contests/abc268/tasks/abc268_c
// Memory Limit: 1024 MB
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

const int maxn = 2e5 + 19;
int cnt[maxn], p[maxn], n;

int main(){
	read(n);
	for(int i = 0; i < n; ++i){
		read(p[i]);
		++cnt[(i - p[i] + n) % n];
		++cnt[(i - p[i] + n + 1) % n];
		++cnt[(i - p[i] + n - 1) % n];
	}
	int ans = 0;
	for(int i = 0; i < n; ++i) ans = std::max(ans, cnt[i]);
	std::cout << ans;
}