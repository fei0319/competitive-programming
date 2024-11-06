#include <bits/stdc++.h>

using ll = long long int;

template <typename T>
const T INF = 1e9;

template <>
const ll INF<ll> = 1e18;

const int MAXN = 2e5 + 19, L = 20;

template <typename T>
class Segment {
    int L, R;
    struct Node {
        T max, tag;
    } tr[MAXN << 2];
    void push_up(int node) {
        tr[node].max = std::max(tr[node << 1].max, tr[node << 1 | 1].max);
    }
    void push_down(int node) {
        if (tr[node].tag) {
            T &tag = tr[node].tag;
            tr[node << 1].max += tag;
            tr[node << 1].tag += tag;
            tr[node << 1 | 1].max += tag;
            tr[node << 1 | 1].tag += tag;
            tag = 0;
        }
    }
    void modify(int node, int L, int R, int l, int r, const T &val) {
        if (l <= L && R <= r) {
            tr[node].max += val;
            tr[node].tag += val;
            return;
        }
        push_down(node);
        int mid = (L + R) / 2;
        if (l <= mid) modify(node << 1, L, mid, l, r, val);
        if (r > mid) modify(node << 1 | 1, mid + 1, R, l, r, val);
        push_up(node);
    }
    T query(int node, int L, int R, int l, int r) {
        if (l <= L && R <= r) return tr[node].max;
        push_down(node);
        int mid = (L + R) / 2;
        T res = -INF<T>;
        if (l <= mid) res = std::max(res, query(node << 1, L, mid, l, r));
        if (r > mid)
            res = std::max(res, query(node << 1 | 1, mid + 1, R, l, r));
        push_up(node);
        return res;
    }

public:
    void set_range(int l, int r) {
        L = l;
        R = r;
    }
    void modify(int l, int r, const T &val) { modify(1, L, R, l, r, val); }
    T query(int l, int r) { return query(1, L, R, l, r); }
};

int n, q;
std::vector<int> G[MAXN];
int fa[MAXN][L];
int dep[MAXN];
int dfn[MAXN], size[MAXN], ind;
Segment<ll> mt;

void dfs1(int node, int f) {
    fa[node][0] = f;
    for (int i = 1; i < L; ++i) {
        fa[node][i] = fa[fa[node][i - 1]][i - 1];
    }

    dep[node] = dep[f] + 1;
    dfn[node] = ++ind, size[node] = 1;

    for (int to : G[node]) {
        if (to == f) continue;
        dfs1(to, node);
        size[node] += size[to];
    }
    mt.modify(dfn[node], dfn[node], dep[node]);
}

bool is_ancestor(int a, int b) {
    return dfn[a] <= dfn[b] && dfn[b] <= dfn[a] + size[a] - 1;
}

std::vector<int> queries[MAXN];
std::vector<int> a[MAXN];
int ans[MAXN];
void modify(int x, const std::vector<int> &a, const int &val) {
    int dep_bound = 0;
    for (int i : a) {
        if (is_ancestor(i, x)) {
            dep_bound = std::max(dep_bound, dep[i]);
        } else {
            mt.modify(dfn[i], dfn[i] + size[i] - 1, val);
        }
    }

    int top = x;
    for (int i = L - 1; i >= 0; --i) {
        if (dep[fa[top][i]] > dep_bound) {
            top = fa[top][i];
        }
    }
    mt.modify(1, n, val);
    mt.modify(dfn[top], dfn[top] + size[top] - 1, -val);
}
void dfs2(int node, int f) {
    for (int id : queries[node]) {
        modify(node, a[id], -INF<int>);
        ans[id] = mt.query(1, n) - 1;
        modify(node, a[id], +INF<int>);
    }

    for (int to : G[node]) {
        if (to == f) continue;
        mt.modify(1, n, 1);
        mt.modify(dfn[to], dfn[to] + size[to] - 1, -2);
        dfs2(to, node);
        mt.modify(1, n, -1);
        mt.modify(dfn[to], dfn[to] + size[to] - 1, 2);
    }
}

int main() {
    std::cin >> n >> q;
    for (int i = 2; i <= n; ++i) {
        int u, v;
        std::cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    mt.set_range(1, n);
    dfs1(1, 0);

    for (int i = 1; i <= q; ++i) {
        int x, k;
        std::cin >> x >> k;

        a[i].resize(k);
        for (int j = 0; j < k; ++j) std::cin >> a[i][j];

        queries[x].push_back(i);
    }

    dfs2(1, 0);

    for (int i = 1; i <= q; ++i) {
        std::cout << ans[i] << '\n';
    }

    return 0;
}
