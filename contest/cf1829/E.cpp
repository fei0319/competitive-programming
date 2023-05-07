#include <bits/stdc++.h>

using ll = long long int;

constexpr int MAXN = 1e3 + 19, MAXS = 1e6 + 19;

int n, m;
int fa[MAXS], sz[MAXS];
int getf(int node) {
	return node == fa[node] ? node : fa[node] = getf(fa[node]);
}
void merge(int x, int y) {
	x = getf(x), y = getf(y);
	if(x != y) {
		fa[y] = x;
		sz[x] += sz[y];
	}
}

int a[MAXN][MAXN];

void solve(void) {
	std::cin >> n >> m;
	for (int i = 1; i <= n * m; ++i) {
		fa[i] = i;
	}
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			std::cin >> a[i][j];
			sz[(i - 1) * m + j] = a[i][j];
		}
	}
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (a[i][j]) {
				if (i > 1 && a[i - 1][j]) {
					merge((i - 1) * m + j, (i - 2) * m + j);
				}
				if (j > 1 && a[i][j - 1]) {
					merge((i - 1) * m + j, (i - 1) * m + j - 1);
				}
			}
		}
	}
	
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (a[i][j] && getf((i - 1) * m + j) == (i - 1) * m + j) {
				ans = std::max(ans, sz[(i - 1) * m + j]);
			}
		}
	}
	std::cout << ans << '\n';
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}