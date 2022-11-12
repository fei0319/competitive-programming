// Problem: P8274 [USACO22OPEN] Balancing a Tree G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8274
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

const int maxn = 1e5 + 19;

int n, l[maxn], r[maxn];
std::vector<int> G[maxn];

int V, upL[maxn], downL[maxn], max[maxn], min[maxn], a[maxn];
void dfs1(int node){
	downL[node] = 0;
	for(int to : G[node])
		dfs1(to), chkmax(downL[node], std::max(downL[to], l[to]));
}

bool dfs2(int node){
	max[node] = 0, min[node] = 1e9;
	for(int to : G[node]){
		upL[to] = std::max({downL[node] - V, upL[node], l[node]});
		if(!dfs2(to)) return false;
		chkmax(max[node], max[to]), chkmin(min[node], min[to]);
	}
	a[node] = std::max({l[node], upL[node] - V, max[node] - V});
	chkmax(max[node], a[node]), chkmin(min[node], a[node]);
	return a[node] <= min[node] + V && a[node] <= r[node];
}

bool check(int v){
	V = v;
	dfs1(1);
	return dfs2(1);
}

void output(int v){
	check(v);
	for(int i = 1; i <= n; ++i) printf("%d ", a[i]);
	puts("");
}

void solve(bool B){
	read(n);
	for(int i = 1; i <= n; ++i) G[i].clear();
	for(int i = 2, p; i <= n; ++i){
		read(p);
		G[p].push_back(i);
	}
	for(int i = 1; i <= n; ++i) read(l[i]), read(r[i]);
//	for(int i = 1; i <= 10; ++i) printf("%d %d\n", i, (int)check(i));
	int l = 0, r = 1e9;
	while(l < r){
		int mid = (l + r) >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%d\n", l);
	if(B) output(l);
}

int main(){
	int T, B; read(T), read(B);
	while(T--){
		solve(B);
	}
}