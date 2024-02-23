#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 1e5 + 19;

int n;
std::vector<std::pair<int, int>> G[MAXN];

ll f[MAXN], g[MAXN];
ll len_f[MAXN], len_g[MAXN];

void dfs1(int node, int fa) {
    ll first = 0, second = 0;
    for (auto [to, w] : G[node]) {
        if (to == fa) {
            continue;
        }
        dfs1(to, node);

        f[node] = std::max(f[node], f[to]);
        if (len_f[to] + w > first) {
            second = first;
            first = len_f[to] + w;
        } else if (len_f[to] + w > second) {
            second = len_f[to] + w;
        }
    }
    f[node] = std::max(f[node], first + second);
    len_f[node] = first;
}

ll ans;
void dfs2(int node, int fa) {
    std::multiset<ll> s, mf;
    for (auto [to, w] : G[node]) {
        if (to == fa) {
            continue;
        }
        s.insert(len_f[to] + w);
        mf.insert(f[to]);
    }
    s.insert(0LL);
    s.insert(0LL);
    s.insert(0LL);
    s.insert(len_g[node]);
    mf.insert(g[node]);
    
    auto it = s.end();
    ans = std::max(ans, *--it + *--it + *--it + *--it);

    for (auto [to, w] : G[node]) {
        if (to == fa) {
            continue;
        }
        s.erase(s.find(len_f[to] + w));
        mf.erase(mf.find(f[to]));

        len_g[to] = *--s.end() + w;
        g[to] = std::max(*--s.end() + *-- --s.end(), *--mf.end());
        ans = std::max(ans, f[to] + g[to] + w * 2);
        dfs2(to, node);

        s.insert(len_f[to] + w);
        mf.insert(f[to]);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ll tot = 0LL;

    std::cin >> n;
    for (int i = 2; i <= n; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);

        tot += w * 2;
    }

    dfs1((n + 1) / 2, 0);
    dfs2((n + 1) / 2, 0);

    std::cout << tot - ans << '\n';

    return 0;
}