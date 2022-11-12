// Problem: C. Jatayu's Balanced Bracket Sequence
// Contest: Codeforces Round #819 (Div. 1 + Div. 2) and Grimoire of Code Annual Contest 2022
// URL: https://codeforces.com/contest/1726/problem/C
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
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) res = res * 10 + ch - 48, ch = getchar();
}

const int maxn = 2e5 + 19;

int n, st[maxn], top;
char s[maxn];

int main(){
	int T; read(T);
	while(T--){
		read(n); scanf("%s", s + 1);
		int ans = n; st[top = 0] = 0;
		for(int i = 1; i <= n * 2; ++i){
			if(s[i] == '(') st[++top] = 0;
			else{
				--top; if(st[top]) --ans;
				st[top] = 1;
			}
		}
		printf("%d\n", ans);
	}
}