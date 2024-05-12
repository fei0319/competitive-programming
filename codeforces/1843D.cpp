#include <cstdio>
#include <vector>

using ll = long long int;

constexpr int MAXN = 2e5 + 19;
std::vector<int> G[MAXN];

int n, q, dp[MAXN];

void dfs(int node, int f) {
    dp[node] = G[node].size() == 1 && f;
    for (int to : G[node])
        if (to != f) {
            dfs(to, node);
            dp[node] += dp[to];
        }
}

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        G[i].clear();
    for (int i = 2; i <= n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        G[x].push_back(y), G[y].push_back(x);
    }
    dfs(1, 0);
    scanf("%d", &q);
    while (q--) {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%lld\n", 1ll * dp[x] * dp[y]);
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--)
        solve();
}