#include <bits/stdc++.h>

using ll = long long int;

constexpr int MAXN = 2e5 + 19;
constexpr int S = 400;
constexpr ll INF = 1e18;

int n, sz[MAXN];
std::vector<int> G[MAXN];
std::vector<ll> f[MAXN], g[MAXN];

int calc(int x) {
    return x * (x + 1) / 2;
}

void dfs(int node, int fa) {
    for (int to : G[node]) {
        if (to != fa) {
            dfs(to, node);
        }
    }

    sz[node] = 1;
    f[node] = {INF, 1};
    for (int to : G[node]) {
        if (to != fa) {
            const int A = std::min(sz[node] + 1, S);
            const int B = std::min(sz[to] + 1, S);
            std::vector<ll> n_f(std::min(A + B - 1, S), INF);
            for (int i = 0; i < A; ++i) {
                for (int j = 0; j < B && i + j < n_f.size(); ++j) {
                    n_f[i + j] = std::min(n_f[i + j], f[node][i] + f[to][j] +
                                                          calc(i + j) -
                                                          calc(i) - calc(j));
                }
            }
            std::swap(f[node], n_f);
            sz[node] += sz[to];

            std::vector<ll> tmp;
            tmp.swap(f[to]);
        }
    }

    sz[node] = 1;
    g[node] = {INF, 2};
    for (int to : G[node]) {
        if (to != fa) {
            const int A = std::min(sz[node] + 1, S);
            const int B = std::min(sz[to] + 1, S);
            std::vector<ll> n_g(std::min(A + B - 1, S), INF);
            for (int i = 0; i < A; ++i) {
                for (int j = 0; j < B && i + j < n_g.size(); ++j) {
                    n_g[i + j] = std::min(
                        n_g[i + j], g[node][i] + g[to][j] +
                                        (calc(i + j) - calc(i) - calc(j)) * 2);
                }
            }
            std::swap(g[node], n_g);
            sz[node] += sz[to];

            std::vector<ll> tmp;
            tmp.swap(g[to]);
        }
    }

    g[node][0] = *std::min_element(f[node].begin() + 1, f[node].end());
    f[node][0] = *std::min_element(g[node].begin() + 1, g[node].end());
}

void solve() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        G[i].clear();
    }
    for (int i = 2; i <= n; ++i) {
        int u, v;
        std::cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs(1, 0);

    ll ans = std::min(f[1][0], g[1][0]);
    std::cout << (ll)n * (n + 1) - ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}