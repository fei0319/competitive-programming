// Problem: D - Bridges
// Contest: AtCoder - AtCoder Regular Contest 143
// URL: https://atcoder.jp/contests/arc143/tasks/arc143_d
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

const int maxn = 2e5 + 19;

struct Edge{
	int to, id;
	Edge(int __to, int __id){to = __to, id = __id; }
};

int n, m, a[maxn], b[maxn];
std::vector<Edge> G[maxn];
int s[maxn];
bool vist[maxn];

void dfs(int node){
	vist[node] = true;
	for(auto it = G[node].begin(); it != G[node].end(); ++it){
		auto to = *it;
		if(!vist[to.to]){
			s[to.id] = (to.to == a[to.id]);
			dfs(to.to);
		}else s[to.id] = (to.to != a[to.id]);
	}
}

int main(){
	read(n), read(m), std::fill(s + 1, s + 1 + m, 3);
	for(int i = 1; i <= m; ++i) read(a[i]);
	for(int i = 1; i <= m; ++i) read(b[i]);
	for(int i = 1; i <= m; ++i){
		G[a[i]].emplace_back(b[i], i);
		G[b[i]].emplace_back(a[i], i);
	}
	for(int i = 1; i <= n; ++i)
		if(!vist[i])
			dfs(i);
	for(int i = 1; i <= m; ++i)
		printf("%d", s[i]);
}

/*





















*/