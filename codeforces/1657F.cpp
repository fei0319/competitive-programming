#include <algorithm>
#include <cassert>
#include <format>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using ll = long long int;

constexpr int MAXN = 2e6 + 19;

int n, q;

std::vector<char> a[MAXN];

std::vector<int> G[MAXN];

int fa[MAXN], dep[MAXN];
void dfs(int node, int f) {
    fa[node] = f, dep[node] = dep[f] + 1;
    for (int to : G[node]) {
        if (to == f) {
            continue;
        }
        dfs(to, node);
    }
}

void add(int x, int a, int y, int b) {
    int tot = n + q;
    G[x + a * tot].push_back(y + b * tot);
    G[y + (1 - b) * tot].push_back(x + (1 - a) * tot);
}

struct Node {
    std::vector<int> v;
    std::string s;
} Q[MAXN];

int dfn[MAXN], low[MAXN], ind;
bool vist[MAXN];
int st[MAXN], top;
int col[MAXN], tot;
void tarjan(int node) {
    st[++top] = node, vist[node] = true;
    dfn[node] = low[node] = ++ind;
    for (int to : G[node]) {
        if (!dfn[to]) {
            tarjan(to);
            low[node] = std::min(low[node], low[to]);
        } else if (vist[to]) {
            low[node] = std::min(low[node], dfn[to]);
        }
    }
    if (dfn[node] == low[node]) {
        ++tot;
        while (st[top + 1] != node) {
            col[st[top]] = tot;
            vist[st[top]] = false;
            --top;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> q;
    for (int i = 2; i <= n; ++i) {
        int u, v;
        std::cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs(1, 0);
    for (int i = 1; i <= n; ++i) {
        G[i].clear();
    }

    for (int p = 1; p <= q; ++p) {
        int x, y;
        std::string s;
        std::cin >> x >> y >> s;

        std::vector<int> v_x, v_y;
        while (dep[x] > dep[y]) {
            v_x.push_back(x);
            x = fa[x];
        }
        while (dep[y] > dep[x]) {
            v_y.push_back(y);
            y = fa[y];
        }
        while (x != y) {
            v_x.push_back(x);
            v_y.push_back(y);
            x = fa[x];
            y = fa[y];
        }
        v_x.push_back(x);
        v_x.insert(v_x.end(), v_y.rbegin(), v_y.rend());

        std::vector<int> v = std::move(v_x);
        assert(v.size() == s.size());
        std::string t(s.rbegin(), s.rend());

        for (int i = 0; i < v.size(); ++i) {
            if (a[v[i]].empty()) {
                if (s[i] != t[i]) {
                    a[v[i]] = {s[i], t[i]};
                    add(p + n, 0, v[i], 0);
                    add(p + n, 1, v[i], 1);
                } else {
                    a[v[i]] = {s[i]};
                    add(p + n, 0, v[i], 0);
                    add(p + n, 1, v[i], 0);
                    add(v[i], 1, v[i], 0);
                }
            } else {
                for (int j = 0; j < a[v[i]].size(); ++j) {
                    if (s[i] == a[v[i]][j]) {
                        add(p + n, 0, v[i], j);
                    }
                    if (t[i] == a[v[i]][j]) {
                        add(p + n, 1, v[i], j);
                    }
                }
                if (std::find(a[v[i]].begin(), a[v[i]].end(), s[i]) ==
                    a[v[i]].end()) {
                    add(p + n, 0, p + n, 1);
                }
                if (std::find(a[v[i]].begin(), a[v[i]].end(), t[i]) ==
                    a[v[i]].end()) {
                    add(p + n, 1, p + n, 0);
                }
            }
        }

        Q[p].v = std::move(v);
        Q[p].s = std::move(s);
    }

    for (int i = 1; i <= (n + q) * 2; ++i) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    for (int i = 1; i <= n + q; ++i) {
        if (col[i] == col[i + n + q]) {
            std::cout << "NO\n";
            return 0;
        }
    }
    std::cout << "YES\n";

    for (int i = 1; i <= n; ++i) {
        if (col[i] <= col[i + n + q]) {
            std::cout << (a[i].empty() ? 'z' : a[i][0]);
        } else {
            std::cout << a[i][1];
        }
    }

    return 0;
}