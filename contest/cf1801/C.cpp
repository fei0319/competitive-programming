#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

int n, dp[maxn], to[maxn];
std::vector<int> a[maxn], tmp;
std::vector<int> s[maxn];

struct Node{
	int id, val;
	bool operator<(const Node &b)const{
		return s[id].back() > s[b.id].back();
	}
};
std::priority_queue<Node> q;

void solve(void){
	std::cin >> n;
	
	tmp.clear();
	for(int i = 1; i <= n; ++i){
		int k; std::cin >> k;
		a[i].resize(k);
		for(int &j : a[i]){
			std::cin >> j;
			tmp.push_back(j);
		}
	}
	
	std::sort(tmp.begin(), tmp.end());
	tmp.resize(std::unique(tmp.begin(), tmp.end()) - tmp.begin());
	for(int i = 1; i <= n; ++i){
		for(int &j : a[i])
			j = std::lower_bound(tmp.begin(), tmp.end(), j) - tmp.begin() + 1;
		s[i].clear();
		int last = 0;
		for(int j : a[i]){
			if(j > last) s[i].push_back(j);
			last = std::max(last, j);
		}
		std::reverse(s[i].begin(), s[i].end());
	//	for(int j : s[i]) std::cout << j << ' ';
	//	std::cout << '\n';
		to[i] = s[i][0];
	}
	
	for(int i = 1; i <= n; ++i) q.push((Node){i, (int)s[i].size()});
	
	int tot = tmp.size();
	for(int i = 1; i <= tot; ++i) dp[i] = 0;
	for(int i = 1; i <= tot; ++i){
		int now = dp[i];
		while(!q.empty() && s[q.top().id].back() <= i){
			Node top = q.top(); q.pop();
			
			top.val = std::max(top.val, dp[i - 1] + (int)s[top.id].size());
			while(!s[top.id].empty() && s[top.id].back() <= i)
				s[top.id].pop_back();
			top.val = std::max(top.val, now + (int)s[top.id].size());
			if(!s[top.id].empty()) q.push(top);
	//		std::cout << top.id << ' ' << top.val << "S\n";
			dp[to[top.id]] = std::max(dp[to[top.id]], top.val);
	//		std::cout << to[top.id] << " is " << dp[to[top.id]] << '\n';
		}
		dp[i + 1] = std::max(dp[i + 1], dp[i]);
	//	std::cout << "dp_" << i << "=" << dp[i] << '\n';
	}
	std::cout << dp[tot] << '\n';
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