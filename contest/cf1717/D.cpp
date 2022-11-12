// Problem: D. Madoka and The Corruption Scheme
// Contest: Codeforces - Codeforces Round #818 (Div. 2)
// URL: https://codeforces.com/contest/1717/problem/D
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

const int maxn = 2e5 + 19, mod = 1e9 + 7;

int qpow(int a, int b){
	int res = 1;
	while(b){
		if(b & 1) res = (ll)res * a % mod;
		a = (ll)a * a % mod, b >>= 1;
	}
	return res;
}

int n, fact[maxn], ifact[maxn], k;
int binom(int n, int m){
	return (ll)fact[n] * ifact[n - m] % mod * ifact[m] % mod;
}

int main(){
	read(n), read(k);
	if(k >= n){
		printf("%d\n", qpow(2, n));
		return 0;
	}
	fact[0] = 1;
	for(int i = 1; i <= n; ++i) fact[i] = (ll)fact[i - 1] * i % mod;
	ifact[n] = qpow(fact[n], mod - 2);
	for(int i = n - 1; i >= 0; --i) ifact[i] = (ll)ifact[i + 1] * (i + 1) % mod;
	int res = binom(n, k);
	for(int i = 1; i <= k; ++i)
		res = (res + (ll)binom(n - i, k - i) * qpow(2, i - 1)) % mod;
	printf("%d\n", res);
		
}