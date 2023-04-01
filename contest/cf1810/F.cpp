#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

int n, m, q, a[maxn];

struct MBase{
	int n;
	struct Tree{
		ll tr[maxn << 2], tag[maxn << 2];
		void build(int node, int L, int R){
			tr[node] = tag[node] = 0;
			if(L == R)
				return;
			int mid = (L + R) / 2;
			build(node << 1, L, mid), build(node << 1 | 1, mid + 1, R);
		}
		void push_up(int node, int L, int R){
			tr[node] = tr[node << 1] + tr[node << 1 | 1] + tag[node] * (R - L + 1);
		}
		void modify(int node, int L, int R, int l, int r, const int &val){
			if(l <= L && R <= r){
				tr[node] += (ll)val * (R - L + 1);
				tag[node] += val;
				return;
			}
			int mid = (L + R) >> 1;
			if(l <= mid) modify(node << 1, L, mid, l, r, val);
			if(r > mid) modify(node << 1 | 1, mid + 1, R, l, r, val);
			push_up(node, L, R);
		}
		ll query(int node, int L, int R, int l, int r){
			if(l <= L && R <= r) return tr[node];
			int mid = (L + R) >> 1;
			ll res = tag[node] * (std::min(R, r) - std::max(L, l) + 1);
			if(l <= mid) res += query(node << 1, L, mid, l, r);
			if(r > mid) res += query(node << 1 | 1, mid + 1, R, l, r);
			return res;
		}
	}t;
	void init(int sz){
		n = sz;
		t.build(1, 1, n);
	}
	void add(int x){
		if(t.query(1, 1, n, x, x) != m - 1){
			t.modify(1, 1, n, x, x, 1);
		}else{
			int l = x, r = n;
			while(l < r){
				int mid = (l + r + 1) / 2;
				if(t.query(1, 1, n, x, mid) == ll(m - 1) * (mid - x + 1))
					l = mid;
				else
					r = mid - 1;
			}
			t.modify(1, 1, n, x, l, -(m - 1));
			t.modify(1, 1, n, l + 1, l + 1, 1);
		}
	}
	void sub(int x){
		if(t.query(1, 1, n, x, x) != 0){
			t.modify(1, 1, n, x, x, -1);
		}else{
			int l = x, r = n;
			while(l < r){
				int mid = (l + r + 1) / 2;
				if(t.query(1, 1, n, x, mid) == 0)
					l = mid;
				else
					r = mid - 1;
			}
			t.modify(1, 1, n, x, l, m - 1);
			t.modify(1, 1, n, l + 1, l + 1, -1);
		}
	}
	int operator()(void){
		int l = 1, r = n;
		while(l < r){
			int mid = (l + r + 1) / 2;
			if(t.query(1, 1, n, mid, n))
				l = mid;
			else
				r = mid - 1;
		}
		// return l;
		if(t.query(1, 1, n, 1, n) == 1)
			return l;
		else
			return l + 1;
	}
	void out(){
		 // for(int i = 7; i >= 1; --i) std::cout << t.query(1, 1, n, i, i);
		 // std::cout << ' ';
	}
}mt;

void solve(void){
	std::cin >> n >> m >> q;
	for(int i = 1; i <= n; ++i) std::cin >> a[i];
	mt.init(n + 40);
	for(int i = 1; i <= n; ++i) mt.add(a[i]);
	mt.out();
	while(q--){
		int x, y; std::cin >> x >> y;
		mt.sub(a[x]);
		mt.out();
		mt.add(a[x] = y);
		mt.out();
		std::cout << mt() << ' ';
	}
	std::cout << '\n';
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