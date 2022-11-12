#include <bits/stdc++.h>

template <typename Tp>
void read(Tp &res){
	static char ch; ch = std::getchar(), res = 0;
	while(!std::isdigit(ch)) ch = std::getchar();
	while(std::isdigit(ch)) res = res * 10 + ch - 48, ch = std::getchar();
}

template <typename Tp>
Tp pabs(const Tp &x){
	return x > 0 ? x : -x;
}

typedef long long int ll;
const int maxn = 5e5 + 19;

struct Node{
	int l, r, id;
}q[maxn];

int n, m, bel[maxn], a[maxn], pos[maxn];
ll ans[maxn];
std::vector<int> all;

std::vector<int> merge(const std::vector<int> &a, const std::vector<int> &b){
	int n = 0, m = 0;
	std::vector<int> res;
	while(n < a.size() || m < b.size()){
		if(n == a.size() || (m < b.size() && b[m] < a[n])) res.emplace_back(b[m++]);
		else res.emplace_back(a[n++]);
	}
	return res;
}

bool insert(int b){
	static bool vist[maxn];
	static int now = n;
	if(vist[b]) return false;
	vist[b] = true;
	std::vector<int> tmp;
	while(now >= 1 && bel[now] >= b) tmp.emplace_back(a[now--]);
	std::sort(tmp.begin(), tmp.end());
	all = merge(all, tmp);
	return true;
}

int prev[maxn], next[maxn];
int st[maxn], top;
ll res;
void del(int x){
	if(prev[x]) res -= pabs(pos[x] - pos[prev[x]]);
	if(next[x]) res -= pabs(pos[next[x]] - pos[x]);
	if(prev[x] && next[x]) res += pabs(pos[next[x]] - pos[prev[x]]);
	if(next[x]) prev[next[x]] = prev[x];
	if(prev[x]) next[prev[x]] = next[x];
}

int main(){
	read(n), read(m);
	int B = std::sqrt(n);
	for(int i = 1; i <= n; ++i) read(a[i]), bel[i] = (i - 1) / B, pos[a[i]] = i;
	for(int i = 1; i <= m; ++i) read(q[i].l), read(q[i].r), q[i].id = i;
	std::sort(q + 1, q + 1 + m,
		[](const Node &a, const Node &b){
			if(bel[a.l] != bel[b.l]) return bel[a.l] > bel[b.l];
			return a.r > b.r;
		}
	);
	
	int L = 0, R = 0;
	for(int i = 1; i <= m; ++i){
		auto node = q[i];
		if(insert(bel[node.l])){
	//		construct a list of B * bel[node.l] + 1 to n
			res = 0;
			for(int j = 1; j < all.size(); ++j)
				prev[all[j]] = all[j - 1], next[all[j - 1]] = all[j], res += pabs(pos[all[j]] - pos[all[j - 1]]);
			prev[all[0]] = 0, next[all.back()] = 0;
			L = bel[node.l] * B + 1, R = n;
		}
		while(R > node.r) del(a[R--]);
	//	memorize
		ll mem = res;
		while(L < node.l) st[++top] = a[L], del(a[L++]);
		ans[node.id] = res;
		while(top){
			int x = st[top--];
			next[prev[x]] = x, prev[next[x]] = x;
		}
		L = bel[node.l] * B + 1;
		res = mem;
	//	rollback
	}
	for(int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);
}