// Problem: B - Number Box
// Contest: AtCoder - AtCoder Beginner Contest 258
// URL: https://atcoder.jp/contests/abc258/tasks/abc258_b
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <cstring>
#include <cstdio>
#include <cctype>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>

typedef long long int ll;

template <typename Tp>
void chkmax(Tp &a, const Tp &b){ a = std::max(a, b); }
template <typename Tp>
void chkmin(Tp &a, const Tp &b){ a = std::min(a, b); }

template <typename Tp>
void read(Tp &res){
	static char ch; ch = getchar(), res = 0;
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) res = res * 10 + ch - 48, ch = getchar();
}

const int maxn = 19;

int n;
std::vector<std::string> vec;
char s[maxn][maxn];
int dx[] = {0, 0, 1, -1, 1, 1, -1, -1},
	dy[] = {1, -1, 0, 0, 1, -1, 1, -1};

int main(){
	read(n);
	for(int i = 0; i < n; ++i)
		scanf("%s", s[i]);
	for(int p = 0; p < 8; ++p)
		for(int x = 0; x < n; ++x)
			for(int y = 0; y < n; ++y){
				std::string str;
				int tx = x, ty = y;
				for(int i = 1; i <= n; ++i){
					str += (s[tx][ty]);
					tx = (tx + dx[p] + n) % n;
					ty = (ty + dy[p] + n) % n;
				}
				vec.push_back(str);
//				std::cout << str << std::endl;
			}
	std::sort(vec.begin(), vec.end());
	std::cout << vec.back();
}

/*





















*/