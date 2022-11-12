// Problem: A. Color the Picture
// Contest: Codeforces - Codeforces Round #810 (Div. 1)
// URL: https://codeforces.com/contest/1710/problem/A
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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

int n, m, k;
int a[maxn];

bool test(int n, int m){
	bool more = false;
	for(int i = k; i >= 0; --i){
		int c = a[i] / m;
		if(c <= 1) return false;
		if(c >= n) return n >= 2 || more;
		n -= c; if(c > 2) more = true;
	}
	return false;
}

int main(){
	int T; read(T);
	while(T--){
		read(n), read(m), read(k);
		for(int i = 1; i <= k; ++i)
			read(a[i]);
		std::sort(a + 1, a + 1 + k);
		puts(test(n, m) || test(m, n) ? "Yes" : "No");
	}
}

/*





















*/