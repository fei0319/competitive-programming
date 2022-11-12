#include <cstdio>
#include <algorithm>

#define int long long

const int maxn = 1e7 + 19;
int T, M, t[10004], w[10004];
int f[2][maxn];

signed main(){
    scanf("%lld%lld", &T, &M);
    for(int i = 1; i <= M; ++i){
    	scanf("%lld%lld", t + i, w + i);
    }
    
    for(int i = 1; i <= M; ++i){
    	for(int j = 0; j < t[i]; ++j)
    		f[i % 2][j] = f[(i - 1) % 2][j];
    	for(int j = t[i]; j <= T; ++j){
	    	f[i % 2][j] = std::max(f[(i - 1) % 2][j], f[(i - 1) % 2][j - t[i]] + w[i]);
	    	f[i % 2][j] = std::max(f[i % 2][j], f[i % 2][j - t[i]] + w[i]);
	    }
	}
	
	int ans = 0;
	for(int x = 0; x <= T; ++x)
		if(f[M % 2][x] > ans){
			ans = f[M % 2][x];
		}
	printf("%lld\n", ans);
}