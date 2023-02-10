#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19, maxb = 31;

struct Base{
	int a[maxb];
	void clear(void){
		for(int i = 0; i < maxb; ++i) a[i] = 0;
	}
	void insert(int b){
		for(int i = maxb - 1; i >= 0; --i)
			if(!a[i]){
				if(b & (1 << i)){
					a[i] = b;
					return;
				}
			}else{
				if(b & (1 << i)) b ^= a[i];
			}
	}
	void insert(const Base &b){
		for(int i = maxb - 1; i >= 0; --i)
			insert(b.a[i]);
	}
	int query(){
		int ans = 0;
		for(int i = maxb - 1; i >= 0; --i)
			if((a[i] & (1 << i)) && !(ans & (1 << i)))
				ans ^= a[i];
		return ans;
	}
}f[maxn], g[maxn];

int n, a[maxn], dfn[maxn], ind, sz[maxn];
std::vector<int> G[maxn];

void dfs1(int node, int fa){
	dfn[node] = ++ind, sz[node] = 1;
	G[node].resize(std::remove(G[node].begin(), G[node].end(), fa) - G[node].begin());
	f[node].insert(a[node]);
	for(int to : G[node]){
		dfs1(to, node);
		f[node].insert(f[to]), sz[node] += sz[to];
	}
}

void dfs2(int node){
	static Base pre[maxn], suf[maxn];
	for(int i = 0; i < G[node].size(); ++i){
		pre[i] = f[G[node][i]];
		if(i != 0) pre[i].insert(pre[i - 1]);
	}
	for(int i = G[node].size() - 1; i >= 0; --i){
		suf[i] = f[G[node][i]];
		if(i != G[node].size() - 1) suf[i].insert(suf[i + 1]);
	}
	
	for(int i = 0; i < G[node].size(); ++i){
		int to = G[node][i];
		g[to] = g[node];
		if(i != 0) g[to].insert(pre[i - 1]);
		if(1 != G[node].size()) g[to].insert(suf[i + 1]);
	}
	
	for(int to : G[node]) dfs2(to);
}

int ans[maxn];
int q;
struct Node{
	int id, r;
};
std::vector<Node> Q[maxn];

void solve(void){
	std::cin >> n; ind = 0;
	for(int i = 1; i <= n; ++i) std::cin >> a[i];
	for(int i = 1; i <= n; ++i) G[i].clear(), f[i].clear(), Q[i].clear();
	for(int i = 1; i < n; ++i){
		int u, v; std::cin >> u >> v;
		G[u].push_back(v), G[v].push_back(u);
	}
	
	dfs1(1, 0);
	g[1].clear(), g[1].insert(a[1]), dfs2(1);
	
	std::cin >> q;
	for(int i = 1; i <= q; ++i){
		int r, v; std::cin >> r >> v;
		Q[v].push_back((Node){i, r});
	}
	
	for(int x = 1; x <= n; ++x){
		std::sort(Q[x].begin(), Q[x].end(), [](const Node &a, const Node &b){
			return dfn[a.r] < dfn[b.r];
		});
		
		int node = x;
		static Base pre[maxn], suf[maxn];
		for(int i = 0; i < G[node].size(); ++i){
			pre[i] = f[G[node][i]];
			if(i != 0) pre[i].insert(pre[i - 1]);
		}
		for(int i = G[node].size() - 1; i >= 0; --i){
			suf[i] = f[G[node][i]];
			if(i != G[node].size() - 1) suf[i].insert(suf[i + 1]);
		}
		
		int now = 0;
		for(auto [id, r] : Q[x]){
			if(dfn[r] < dfn[x] || dfn[r] >= dfn[x] + sz[x]){
				ans[id] = f[x].query();
			}else if(dfn[r] == dfn[x]){
				ans[id] = f[1].query();
			}else{
				while(dfn[r] >= dfn[G[x][now]] + sz[G[x][now]]) ++now;
				Base tmp = g[node];
				if(now != 0) tmp.insert(pre[now - 1]);
				if(now != G[node].size() - 1) tmp.insert(suf[now + 1]);
				ans[id] = tmp.query();
			}

		}
	}
	
	for(int i = 1; i <= q; ++i) std::cout << ans[i] << '\n';
}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	int T;
	std::cin >> T;
	
	while(T--){
		solve();
	}
	
	return 0;
}