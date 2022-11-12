// Problem: P8190 [USACO22FEB] Cow Camp G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8190
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
typedef long long int ll;
typedef long double real;
template <typename Tp> void chkmax(Tp &a, const Tp &b){ a = std::max(a, b); }
template <typename Tp> void chkmin(Tp &a, const Tp &b){ a = std::min(a, b); }
template <typename Tp> void read(Tp &res){
	static char ch; ch = getchar(), res = 0;
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) res = res * 10 + ch - 48, ch = getchar();
}

const int maxn = 1e3 + 19;
const real eps = 0;

int t, k;
real p[maxn], E[maxn], s[maxn], binom[maxn][maxn];
real ans;

struct Matrix{
	real a[2][2];
	Matrix(){a[0][0] = a[0][1] = a[1][0] = a[1][1] = 0; }
	Matrix operator*(const Matrix &b){
		Matrix res;
		for(int i = 0; i < 2; ++i)
			for(int j = 0; j < 2; ++j)
				for(int k = 0; k < 2; ++k)
					res.a[i][j] += a[i][k] * b.a[k][j];
		return res;
	}
};

Matrix qpow(Matrix a, int b){
	Matrix res = a; --b;
	while(b){
		if(b & 1) res = res * a;
		a = a * a, b >>= 1;
	}
	return res;
}

real check(int d, int i){
	real pk = d * std::log(s[i]), ed = E[i + 1] / (s[i] - 1) + ans;
	return std::exp(pk) * ed - E[i + 1] / (s[i] - 1);
}

int main(){
	read(t), read(k), --t;
	binom[0][0] = 1;
	real p2 = 1;
	for(int i = 1; i <= t; ++i){
		for(int j = 0; j < i; ++j)
			binom[i][j] = binom[i - 1][j - 1] + binom[i - 1][j];
		binom[i][i] = 1; p2 /= 2;
	}
	for(int i = 0; i <= t; ++i)
		s[i] = p[i] = binom[t][i] * p2;
	for(int i = 1; i <= t; ++i)
		s[i] += s[i - 1];
	for(int i = t; i >= 0; --i)
		E[i] = E[i + 1] + p[i] * i;
	int x = 0;
	while(x < k){
		int v = ans;
		int l = x + 1, r = k;
		while(l < r){
			int mid = (l + r) >> 1;
			if((ll)(check(mid - x, v)) > v) r = mid;
			else l = mid + 1;
		}
		ans = check(l - x, v), x = l;
	}
	ans = ans + 1;
	printf("%.18Lf\n", ans);
}