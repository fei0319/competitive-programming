// Problem: D - Trophy
// Contest: AtCoder - AtCoder Beginner Contest 258
// URL: https://atcoder.jp/contests/abc258/tasks/abc258_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <cstring>
#include <cstdio>
#include <cctype>
#include <cmath>

#include <algorithm>
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

int n, a, b, x;
ll ans = 9e18, res;

int main(){
	read(n), read(x);
	int minb = 1e9;
	for(int i = 1; i <= n; ++i){
		read(a), read(b), chkmin(minb, b);
		res += a + b;
		chkmin(ans, res + ll(x - i) * minb);
	}
	printf("%lld\n", ans);
}

/*





















*/