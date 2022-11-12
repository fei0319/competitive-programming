// Problem: P8099 [USACO22JAN] Minimizing Haybales P
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8099
// Memory Limit: 512 MB
// Time Limit: 4000 ms
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

std::mt19937 rng(std::time(0));
int n, k;
struct Tree{
	int rt, tot;
	struct Node{
		int ls, rs;
		int sz, mn, mx, v;
		unsigned fate;
	}t[maxn * 20];
	void output(int x){
		if(!x) return;
		output(t[x].ls), printf("%d\n", t[x].v), output(t[x].rs);
	}
	void push_up(int x){
		t[x].sz = t[t[x].ls].sz + t[t[x].rs].sz + 1;
		t[x].mn = std::min({t[x].v, t[t[x].ls].mn, t[t[x].rs].mn});
		t[x].mx = std::max({t[x].v, t[t[x].ls].mx, t[t[x].rs].mx});
	}
	std::pair<int, int> split(int x, const int &val){
		if(!x) return {0, 0};
		if(t[t[x].ls].sz >= val){
			auto tmp(split(t[x].ls, val));
			t[x].ls = tmp.second, push_up(x);
			return {tmp.first, x};
		}else{
			auto tmp(split(t[x].rs, val - t[t[x].ls].sz - 1));
			t[x].rs = tmp.first, push_up(x);
			return {x, tmp.second};
		}
	}
	int merge(int x, int y){
		if(!x || !y) return x | y;
		if(t[x].fate > t[y].fate){
			t[x].rs = merge(t[x].rs, y), push_up(x);
			return x;
		}else{
			t[y].ls = merge(x, t[y].ls), push_up(y);
			return y;
		}
	}
	int newnode(int val){
		++tot;
		t[tot].fate = rng();
		t[tot].sz = 1, t[tot].mn = t[tot].mx = t[tot].v = val;
		return tot;
	}
	int find(int x, int h){
		if(!x) return 0;
		if(t[x].mn >= h - k && t[x].mx <= h + k)
			return t[x].sz;
		if(t[t[x].rs].mn >= h - k && t[t[x].rs].mx <= h + k){
			if(t[x].v >= h - k && t[x].v <= h + k)
				return find(t[x].ls, h) + 1 + t[t[x].rs].sz;
			else
				return t[t[x].rs].sz;
		}
		else return find(t[x].rs, h);
	}
	int upper_bound(int x, const int &val){
		if(!x) return 0;
		if(t[x].mx <= val) return t[x].sz + 1;
		if(t[t[x].ls].mx > val)
			return upper_bound(t[x].ls, val);
		else if(t[x].v > val)
			return t[t[x].ls].sz + 1;
		else
			return t[t[x].ls].sz + 1 + upper_bound(t[x].rs, val);
	}
}mt;

void solve(int h){
	int p = mt.t[mt.rt].sz - mt.find(mt.rt, h);
//	printf("p=%d\n", p);
	auto t1(mt.split(mt.rt, p));
//	printf("q=%d\n", mt.upper_bound(t1.second, h));
	auto t2(mt.split(t1.second, mt.upper_bound(t1.second, h) - 1));
	mt.rt = mt.merge(t1.first, mt.merge(t2.first, mt.merge(mt.newnode(h), t2.second)));
//	mt.output(mt.rt);
}

int main(){
	read(n), read(k);
	mt.t[0].mn = 2e9;
	mt.t[0].mx = -2e9;
	for(int i = 1, x; i <= n; ++i) read(x), solve(x);
	mt.output(mt.rt);
}