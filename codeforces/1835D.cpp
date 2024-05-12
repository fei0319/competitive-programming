#include <bits/stdc++.h>

using ll = int64_t;

constexpr int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

const int MAXN = 1e5 + 19;

int n, m;
ll k;
std::vector<int> G[MAXN], R[MAXN];

bool vist[MAXN];
int dfn[MAXN], low[MAXN], ind;
int st[MAXN], top;
bool instack[MAXN];
std::vector<std::vector<int>> scc;
void dfs(int node) {
    vist[node] = true;
    dfn[node] = low[node] = ++ind;
    st[++top] = node;
    instack[node] = true;

    for (int to : G[node]) {
        if (!vist[to]) {
            dfs(to);
            low[node] = std::min(low[node], low[to]);
        } else if (instack[to]) {
            low[node] = std::min(low[node], low[to]);
        }
    }
    if (dfn[node] == low[node]) {
        std::vector<int> c;
        while (st[top] != node) {
            instack[st[top]] = false;
            c.push_back(st[top--]);
        }
        instack[st[top]] = false;
        c.push_back(st[top--]);
        scc.push_back(std::move(c));
    }
}

int dep[MAXN], rdep[MAXN];
bool in[MAXN];
ll solve(const std::vector<int> &c) {
    if (c.size() == 1) {
        return 0;
    }

    int rt = c.back();

    for (int i : c) {
        in[i] = true;
    }

    std::vector<int> cycles;
    std::function<void(int)> dfs = [&](int node) -> void {
        vist[node] = true;
        instack[node] = true;

        for (int to : G[node]) {
            if (in[to]) {
                if (vist[to]) {
                    if (instack[to]) {
                        cycles.push_back(dep[node] - dep[to] + 1);
                    } else {
                        cycles.push_back(dep[node] + rdep[to] + 1);
                    }
                } else {
                    dep[to] = dep[node] + 1;
                    dfs(to);
                }
            }
        }

        instack[node] = false;
    };
    std::function<void(int)> dfs1 = [&](int node) -> void {
        vist[node] = true;

        for (int to : R[node]) {
            if (in[to]) {
                if (!vist[to]) {
                    rdep[to] = rdep[node] + 1;
                    dfs1(to);
                }
            }
        }
    };
    dfs1(rt);
    for (int i : c) {
        vist[i] = false;
    }
    dfs(rt);

    for (int i : c) {
        in[i] = false;
    }

    int g = 0;
    for (int len : cycles) {
        g = gcd(g, len);
        if (g == 1) {
            break;
        }
    }

    if (g == 1) {
        return (ll)c.size() * (c.size() - 1) / 2 + c.size();
    }

    std::vector<std::vector<int>> s(
        g); // dep[u] - rdep[u] = i (mod g) for u in s[i]
    std::vector<int> b(g);
    for (int i : c) {
        int reminder = ((dep[i] - rdep[i]) % g + g) % g;
        s[reminder].push_back(i);
    }

    ll res = 0;
    for (int r = 0; r < g; ++r) {
        for (int i : s[r]) {
            b[((k - dep[i]) % g + g) % g] += 1;
            res += b[rdep[i] % g];
        }
        for (int i : s[r]) {
            b[((k - dep[i]) % g + g) % g] -= 1;
        }
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m >> k;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        std::cin >> u >> v;
        G[u].push_back(v);
        R[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i) {
        if (!vist[i]) {
            dfs(i);
        }
    }

    std::fill(vist, vist + n + 1, false);
    ll ans = 0;
    for (const auto &c : scc) {
        ans += solve(c);
    }

    std::cout << ans << '\n';

    return 0;
}