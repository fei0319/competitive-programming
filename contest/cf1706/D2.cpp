// Problem: D2. Chopping Carrots (Hard Version)
// Contest: Codeforces - Codeforces Round #809 (Div. 2)
// URL: https://codeforces.com/contest/1706/problem/D2
// Memory Limit: 64 MB
// Time Limit: 4000 ms
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

const int maxn = 1e5 + 19;

int n, k, st[maxn], top, res[maxn];

int main(){
	int T; read(T);
	while(T--){
		read(n), read(k); int minv = 1e5;
		for(int i = 0; i < maxn; ++i) res[i] = 0;
		for(int i = 1; i <= n; ++i){
			int a; read(a), top = 0; chkmin(minv, a);
			for(int d = 1; d <= k && d <= a; d = a / (a / d) + 1)
				st[++top] = a / d;
			if(k > a) st[++top] = 0;
		//	for(int j = 1; j <= top; ++j) printf("%d ", st[j]);
			//puts("");
			for(int i = 1; i < top; ++i)
				chkmax(res[st[i + 1] + 1], st[i]);
			chkmax(res[0], st[top]);
		}
		int ans = res[0] - 0;
		for(int i = 1; i <= minv; ++i){
			res[i] = std::max(res[i], res[i - 1]);
			chkmin(ans, res[i] - i);
		}
		printf("%d\n", ans);
	}
}

/*





















*/