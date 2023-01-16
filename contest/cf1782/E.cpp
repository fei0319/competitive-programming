#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

struct Node{
	int l, r, id;
	Node(int __l = 0, int __r = 0, int __id = 0){
		l = __l, r = __r, id = __id;
	}
};

int n, u[maxn], l[maxn], d[maxn], r[maxn];
std::vector<Node> a[3];
std::vector<int> b;

int find_left(int v){
	int L = 0, R = b.size() - 1;
	while(L < R){
		int mid = (L + R) >> 1;
		if(r[b[mid]] >= v) R = mid;
		else L = mid + 1;
	}
	return L;
}

int find_right(int v){
	int L = 0, R = b.size() - 1;
	while(L < R){
		int mid = (L + R + 1) >> 1;
		if(l[b[mid]] <= v) L = mid;
		else R = mid - 1;
	}
	return L;
}

void deal(std::vector<Node> a, int f){
	
	std::vector<int> c;
	for(auto [_l, _r, id] : a)
		if(c.empty() || _r > r[c.back()]){
			if(c.size() && _l <= r[c.back()]) l[id] = r[c.back()] + 1;
			c.push_back(id);
		}else{
			u[id] = 2, d[id] = 1;
		}
		
	for(int id : c){
		if(b.empty()) continue;
		int L = find_left(l[id]), R = find_right(r[id]);
		if(L == R && l[b[L]] <= l[id] && r[b[R]] >= r[id]){
			u[id] = 2, d[id] = 1;
			continue;
		}
		for(int i = L; i <= R; ++i){
			if(l[id] <= l[b[i]] && r[b[i]] <= r[id]){
				if(f == 1) u[b[i]] = 2;
				else d[b[i]] = 1;
			}else{
				if(l[id] <= r[b[i]] && l[id] >= l[b[i]]) l[id] = r[b[i]] + 1;
				if(r[id] >= l[b[i]] && r[id] <= r[b[i]]) r[id] = l[b[i]] - 1;
			}
			if(l[id] > r[id]) u[id] = 2, d[id] = 1;
		}
	}
}

void solve(void){
	a[0].clear(), a[1].clear(), a[2].clear();
	
	std::cin >> n;
	
	for(int i = 1; i <= n; ++i){
		std::cin >> u[i] >> l[i] >> d[i] >> r[i];
		if(u[i] == 1) a[1].emplace_back(l[i], r[i], i);
		if(d[i] == 2) a[2].emplace_back(l[i], r[i], i);
		if(u[i] == 1 && d[i] == 2) a[0].emplace_back(l[i], r[i], i);
	}
	
	ll ans = 0;
	for(int i = 1; i <= 2; ++i){
		std::sort(a[i].begin(), a[i].end(), [](const Node &x, const Node &y){
			return x.l < y.l;
		});
		std::vector<std::pair<int, int>> b;
		for(auto [l, r, id] : a[i]){
			if(b.size() && l <= b.back().second)
				b.back().second = std::max(b.back().second, r);
			else
				b.emplace_back(l, r);
		}
		for(auto [l, r] : b) ans += r - l + 1;
		a[i].resize(std::remove_if(a[i].begin(), a[i].end(), [](const Node &b){
			return u[b.id] == 1 && d[b.id] == 2;
		}) - a[i].begin());
	}
	std::cout << ans << '\n';
	
	for(int i = 0; i <= 2; ++i)
		std::sort(a[i].begin(), a[i].end(), [](const Node &x, const Node &y){
			if(x.l != y.l) return x.l < y.l;
			return x.r > y.r;
		});
	
	b.clear();
	for(auto [_l, _r, id] : a[0])
		if(b.empty() || _r > r[b.back()]){
			if(b.size() && _l <= r[b.back()]) l[id] = r[b.back()] + 1;
			b.push_back(id);
		}else{
			u[id] = 2, d[id] = 1;
		}
	
	deal(a[1], 1), deal(a[2], 2);
	for(int i = 1; i <= n; ++i){
		if(u[i] == 2 && d[i] == 1) std::cout << "0 0 0 0\n";
		else std::cout << u[i] << ' ' << l[i] << ' ' << d[i] << ' ' << r[i] << '\n';
	}
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