#include <cstdio>
#include <vector>

constexpr int maxn = 2e5 + 19;

std::vector<int> G[maxn];
int n, p[maxn], dp[maxn];

void dfs(int node) {
    int g1 = 0, g2 = 0;
    for (int to : G[node]) {
        dfs(to);
        if (dp[to] >= g1) g2 = g1, g1 = dp[to];
        else if (dp[to] > g2) g2 = dp[to];
    }
    dp[node] = std::max(g1 - 1, g2) + 1;
}

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", p + i);
        G[i].clear();
    }
    for (int i = 2; i <= n; ++i) G[p[i]].push_back(i);

    dfs(1);
    printf("%d\n", dp[1]);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) solve();
}