// Problem: A - Anyway Takahashi
// Contest: AtCoder - UNICORN Programming Contest 2022(AtCoder Beginner Contest 269)
// URL: https://atcoder.jp/contests/abc269/tasks/abc269_a
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

int main(){
	int a, b, c, d;
	scanf("%d%d%d%d", &a, &b, &c, &d);
	std::cout << (a + b) * (c - d) << "\nTakahashi";
}