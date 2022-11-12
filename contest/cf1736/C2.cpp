#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

int n, q, a[maxn], s[maxn];
int st[maxn], top;
ll ss[maxn];

struct Node{
	int p, x, id;
}node[maxn];

ll sum[maxn], ans[maxn];

void ins(int x){
	int v = a[x] - x;
	while(a[st[top]] - st[top] >= v){
		--top;
	}
	st[top + 1] = x;
	ss[top + 1] = ll(st[top] - x) * v + ss[top];
	++top;
}

ll calc(int x){
	if(!top){
		return 0;
	}
	if(a[st[1]] - st[1] > x){
		return ll(st[0] - st[top]) * x;
	}
	int l = 1, r = top;
	while(l < r){
		int mid = (l + r + 1) >> 1;
		if(a[st[mid]] - st[mid] <= x){
			l = mid;
		}else{
			r = mid - 1;
		}
	}
	return ll(st[l] - st[top]) * x + ss[l];
}

void solve(void){
	std::cin >> n;
	for(int i = 1; i <= n; ++i){
		std::cin >> a[i];
		s[i] = std::min(s[i - 1], a[i] - i);
		sum[i] = sum[i - 1] + s[i];
	}
	std::cin >> q;
	for(int i = 1; i <= q; ++i){
		std::cin >> node[i].p >> node[i].x;
		node[i].id = i;
	}
	std::sort(node + 1, node + 1 + q, [](const Node &a, const Node &b){
		return a.p > b.p;
	});
	int ptr = n + 1;
	st[0] = n + 1;
	for(int i = 1; i <= q; ++i){
		while(ptr > node[i].p + 1){
			ins(--ptr);
		}
		int x = std::min(s[node[i].p - 1], node[i].x - node[i].p);
		 // std::cout << "solving " << node[i].id << std::endl;
		 // for(int j = 1; j <= top; ++j){
			 // std::cout << st[j] << std::endl;
		 // }
		 // std::cout << calc(x) << "\n";
		ans[node[i].id] = sum[node[i].p - 1] + x + calc(x);
	}
	ll bas = (ll)n * (n + 1) / 2;
	for(int i = 1; i <= q; ++i){
		std::cout << ans[i] + bas << std::endl;
	}
}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	int T;
	T = 1;
	
	while(T--){
		solve();
	}
	
	return 0;
}