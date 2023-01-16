#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 6e5 + 19, N = 3e5, inf = 1e9;

int n, a[maxn], s, t;
int vist[maxn];

int dist[maxn], from[maxn];

struct Edge{
	int to, next;
}edge[maxn * 13];
int head[maxn], cnt;

inline void add(int from, int to){
	edge[++cnt].to = to;
	edge[cnt].next = head[from];
	head[from] = cnt;
}

void dijkstra(int s){
	for(int i = 1; i <= N + N; ++i) dist[i] = inf, vist[i] = 0;
	vist[s] = 0, dist[s] = 0;
	
	static int q[maxn], h, t;
	q[h = t = 0] = s;
	
	while(h <= t){
		int node = q[h++];
		if(vist[node]) continue;
		vist[node] = 1;
		
		for(int i = head[node]; i; i = edge[i].next){
			int to = edge[i].to;
			if(dist[to] == inf){
				dist[to] = dist[node] + 1;
				q[++t] = to, from[to] = node;
			}
		}
	}
}

void solve(void){
	std::cin >> n;
	for(int i = 1; i <= n; ++i){
		std::cin >> a[i];
		vist[a[i]] = 1;
	}
	std::cin >> s >> t;
	
	if(a[s] == a[t]){
		if(s == t){
			std::cout << "1\n";
			std::cout << s;
			return;
		}
		if(a[s] == 1){
			std::cout << "-1\n";
			return;
		}
		std::cout << "2\n";
		std::cout << s << ' ' << t;
		return;
	}
	
	for(int i = 2; i <= N; ++i)
		for(int j = i; j <= N; j += i)
			if(vist[j]){
				add(j, N + i);
				add(N + i, j);
			}
	dijkstra(a[s]);
	
	if(dist[a[t]] == inf){
		std::cout << "-1\n";
		return;
	}
	for(int i = 1; i <= n; ++i){
		if(a[i] != a[s] && a[i] != a[t])
			vist[a[i]] = i;
	}
	vist[a[s]] = s, vist[a[t]] = t;
		
	std::vector<int> ans;
	while(t != s){
		ans.push_back(t);
		t = vist[from[from[a[t]]]];
	}
	ans.push_back(s);
	std::reverse(ans.begin(), ans.end());
	std::cout << ans.size() << std::endl;
	for(int i : ans) std::cout << i << ' ';
}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	int T = 1;
	
	while(T--){
		solve();
	}
	
	return 0;
}