#include <bits/stdc++.h>

using ll = long long int;

constexpr int MAXN = 2e6 + 19;
constexpr int MAXS = 3e7;

struct Edge {
	int to, next;
} edge[MAXS];
int head[MAXN], tot;
void add(int from, int to) {
	++tot;
	edge[tot].to = to;
	edge[tot].next = head[from];
	head[from] = tot;
}

void solve() {
	int n, m;
	std::cin >> n >> m;
	
	ll ans = 0;
	for (int i = 1; i <= std::min(n, m); ++i) {
		int a = n / i, b = m / i;
		
		for (int v = head[i]; v; v = edge[v].next) {
			int d = edge[v].to;
			int l = std::max(1, d - b), r = std::min(a, d - 1);
			if (l > r) {
				continue;
			}
			
			
			for (int i = l; i <= r; ++i) {
				if (std::gcd(i, d) == 1) {
					++ans;
				}
			}
		}
	}
	std::cout << ans << std::endl;
}

int main() {
	const int N = 2e6;
	for (int i = 1; i <= N; ++i) {
		for (int j = i; j <= N; j += i) {
			add(j, i);
		}
	}
	
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}