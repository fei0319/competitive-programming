#include <bits/stdc++.h>

constexpr int maxn = 1e7 + 19;

int n, k, a[maxn], b[maxn], s[maxn];

int q[maxn], h = 1, t;
int qv[maxn], hv = 1, tv, tag;
int sum;

int main(){
	scanf("%d%d", &n, &k);
	assert(k >= 1);
	for(int i = 1; i <= n; ++i) scanf("%d", a + i);
	
	int ans = 1;
	
	for(int i = 1; i <= n; ++i){
		s[i] = s[i - 1] + (a[i] ? a[i] : 1);
		if(a[i]){
			if(h > t) sum = std::max(sum + a[i], a[i]);
			else{
				int next = std::max(b[q[t]] + tag + a[i], a[i]);
				tag += a[i], b[q[t]] = next - tag;
				while(hv < tv && b[qv[tv]] >= b[qv[tv - 1]])
					qv[tv - 1] = qv[tv], --tv;
			}
		}else{
			q[++t] = i, qv[++tv] = i;
			tag += 1, b[i] = 1 - tag;
			while(t - h + 1 > k){
				int pop = q[h++];
				sum = std::max(sum - 1, -1);
				for(int j = pop + 1; j < q[h]; ++j)
					sum = std::max(sum + a[j], a[j]);
			}
			while(hv < tv && b[qv[tv]] >= b[qv[tv - 1]])
				qv[tv - 1] = qv[tv], --tv;
			while(qv[hv] < q[h]) ++hv;
		}
		assert(q[t] == qv[tv] || h > t);
		if(h <= t){
			ans = std::max(ans, std::max(s[i] - s[q[h] - 1] + std::max(sum, 0), b[qv[hv]] + tag));
		}else{
			ans = std::max(ans, sum);
		}
	}
	printf("%d\n", ans);
	
	return 0;
}