// Problem: F1. Array Shuffling
// Contest: Codeforces - Codeforces Global Round 20
// URL: https://codeforces.com/contest/1672/problem/F1
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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

const int maxn = 2e5 + 19;
std::priority_queue<std::pair<int, int> > q;

int n, cnt[maxn], a[maxn];
std::vector<int> pos[maxn];

int main(){
	int T; read(T);
	while(T--){
		read(n);
		std::vector<int> all;
		for(int i = 1; i <= n; ++i) read(a[i]), ++cnt[a[i]], pos[a[i]].push_back(i);
		for(int i = 1; i <= n; ++i) if(cnt[i]) all.push_back(i);
		while(all.size()){
			std::vector<int> tmp; tmp.swap(all);
			for(int i : tmp){
				--cnt[i]; if(cnt[i]) all.push_back(i);
			}
			if(!tmp.size()) return 0;
			tmp.push_back(tmp.front());
			for(int i = 1; i < (int)tmp.size(); ++i){
				a[pos[tmp[i - 1]].back()] = tmp[i], pos[tmp[i - 1]].pop_back();
			}
		}
		for(int i = 1; i <= n; ++i) printf("%d ", a[i]);
		puts("");
	}
}