#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e6 + 19;

int n, m, a[maxn], b[maxn], p[maxn], rest[maxn];
std::vector<int> pos[maxn];

int tmp[maxn], tot;

bool check(int l, int r, int x){
//	std::cout << l << ' ' << r << ' ' << tmp[x] << std::endl;
	if(x == 0) return true;
	if(l > r) return true;
	
	int need = 0;
	
	std::vector<int> cur;
	cur.push_back(l - 1);
	for(auto it = std::lower_bound(pos[x].begin(), pos[x].end(), l); it != pos[x].end() && *it <= r; ++it){
//		std::cout << *it << '\n';
		if(a[*it] > b[*it]) need = 1;
		else if(a[*it] < b[*it]) return false;
		cur.push_back(*it);
	}
	cur.push_back(r + 1);
	
	if(need > rest[x]){
//		std::cout << "N" << need << rest[x] << '\n';
		return false;
	}
	rest[x] -= need;
//	if(x == 2) std::cout << "DELing2\n";
	
	for(int i = 0; i + 1 < cur.size(); ++i)
		if(!check(cur[i] + 1, cur[i + 1] - 1, x - 1)){
//			std::cout << "FAIL:" << cur[i] + 1 << ' ' << cur[i + 1] - 1 << ' ' << x - 1 << '\n';
			return false;
		}
	return true;
}

void solve(void){
	std::cin >> n;
	tot = 0;
	for(int i = 1; i <= n; ++i){
		std::cin >> a[i];
		tmp[++tot] = a[i];
	}
	for(int i = 1; i <= n; ++i){
		std::cin >> b[i];
		tmp[++tot] = b[i];
	}
	std::cin >> m;
	for(int i = 1; i <= m; ++i){
		std::cin >> p[i];
		tmp[++tot] = p[i];
	}
	
	std::sort(tmp + 1, tmp + 1 + tot);
	tot = std::unique(tmp + 1, tmp + 1 + tot) - tmp - 1;
	for(int i = 1; i <= tot; ++i) rest[i] = 0, pos[i].clear();
	
	for(int i = 1; i <= n; ++i){
		a[i] = std::lower_bound(tmp + 1, tmp + 1 + tot, a[i]) - tmp;
		b[i] = std::lower_bound(tmp + 1, tmp + 1 + tot, b[i]) - tmp;
		pos[b[i]].push_back(i);
	}
	for(int i = 1; i <= m; ++i){
		p[i] = std::lower_bound(tmp + 1, tmp + 1 + tot, p[i]) - tmp;
		++rest[p[i]];
	}
	
	if(check(1, n, tot)) std::cout << "YES\n";
	else std::cout << "NO\n";
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