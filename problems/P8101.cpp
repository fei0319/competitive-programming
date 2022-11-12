// Problem: P8101 [USACO22JAN] Multiple Choice Test P
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8101
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
	bool flag = false;
	while(!isdigit(ch)) flag |= (ch == '-'), ch = getchar();
	while(isdigit(ch)) res = res * 10 + ch - 48, ch = getchar();
	if(flag) res = -res;
}

const int maxn = 2e5 + 19;

struct Node{
	int x, y;
	Node(int __x = 0, int __y = 0){x = __x, y = __y; }
	bool operator<(const Node &b)const{
		return x != b.x ? x < b.x : y < b.y;
	}
	Node operator+(const Node &b)const{
		return Node(x + b.x, y + b.y);
	}
	Node operator-(const Node &b)const{
		return Node(x - b.x, y - b.y);
	}
	bool operator*(const Node &b)const{
		return (ll)x * b.y - (ll)b.x * y > 0;
	}
};

void reorder(std::vector<Node> &a){
	int id = 0, sz = a.size();
	for(int i = 1; i < sz; ++i) if(a[i] < a[id]) id = i;
	std::vector<Node> b;
	for(int i = id; i < sz; ++i) b.push_back(a[i]);
	for(int i = 0; i < id; ++i) b.push_back(a[i]);
	a.swap(b);
}

struct Convex{
	std::vector<Node> v;
	Convex(std::vector<Node> __v = {}){v = __v;}
	Convex operator+(const Convex &__b){
		std::vector<Node> a(v), b(__b.v);
		a.push_back(a.front()), b.push_back(b.front());
		int ta = 1, tb = 1;
		std::vector<Node> edge;
		while(ta < a.size() || tb < b.size()){
			if(tb == b.size() || (ta < a.size() && (a[ta] - a[ta - 1]) * (b[tb] - b[tb - 1])))
				edge.emplace_back(a[ta] - a[ta - 1]), ++ta;
			else
				edge.emplace_back(b[tb] - b[tb - 1]), ++tb;
		}
		edge.pop_back();
		std::vector<Node> res;
		res.emplace_back(a.front() + b.front());
		for(auto i : edge) res.push_back(res.back() + i);
		return res;
	}
};

Convex construct(std::vector<Node> a){
	std::sort(a.begin(), a.end());
	std::sort(a.begin() + 1, a.end(),
		[&](const Node &x, const Node &y){
			return (x - a.front()) * (y - a.front());
		}
	);
	static int st[maxn], top; top = 0;
	st[++top] = 0;
	for(int i = 1; i < a.size(); ++i){
		while(top >= 2 && (a[i] - a[st[top - 1]]) * (a[st[top]] - a[st[top - 1]]))
			--top;
		st[++top] = i;
	}
	std::vector<Node> res;
	for(int i = 1; i <= top; ++i) res.emplace_back(a[st[i]]);
	reorder(res);
	return res;
}

int n;

Convex solve(std::vector<Convex> a){
	if(a.size() == 1) return a[0];
	std::vector<Convex> b;
	while(b.size() < a.size()) b.push_back(a.back()), a.pop_back();
	return solve(a) + solve(b);
}

int main(){
	read(n);
	std::vector<Convex> all;
	for(int i = 1; i <= n; ++i){
		int g; read(g);
		std::vector<Node> a(g);
		for(int j = 0; j < g; ++j)
			read(a[j].x), read(a[j].y);
		all.push_back(construct(a));
	}
	Convex res = solve(all);
	ll ans = 0ll;
	for(auto i : res.v)
		chkmax(ans, (ll)i.x * i.x + (ll)i.y * i.y);
	printf("%lld\n", ans);
}