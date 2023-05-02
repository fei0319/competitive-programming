#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 5e3 + 19;

int n, dist[maxn], d[maxn];

void add(int x){
	printf("+ %d\n", x);
	std::fflush(stdout);
	scanf("%d", &x);
}

int query(int i, int j){
	printf("? %d %d\n", i, j);
	std::fflush(stdout);
	scanf("%d", &i);
	return i;
}

void out(){
	for(int i = 1; i <= n; ++i)
		if(d[i] % 2 == 0)
			printf("%d ", d[i] / 2 + 1);
		else
			printf("%d ", n - d[i] / 2);
}

void work(void){
	std::cin >> n;
	add(1 + n), add(2 + n);
	int max = 1;
	for(int i = 2; i <= n; ++i){
		dist[i] = query(1, i);
		if(dist[i] > dist[max]){
			max = i;
		}
	}
	d[max] = 0;
	for(int i = 1; i <= n; ++i){
		if(i == max) continue;
		d[i] = query(max, i);
	}
	printf("! ");
	out();
	for(int i = 1; i <= n; ++i) d[i] = n - 1 - d[i];
	out();
	puts("");
	std::fflush(stdout);
	scanf("%d", &n);
}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	int T;
	std::cin >> T;
	
	while(T--){
		work();
	}
	
	return 0;
}