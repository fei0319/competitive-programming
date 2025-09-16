#include <algorithm>
#include <cstdio>

using ll = long long int;
constexpr int MAXN = 2e5 + 19;
constexpr ll inf = 1e18;

int n, k, A;
struct Node {
    int x, y, c;
} node[MAXN];

struct Tree {
    ll min[MAXN << 2], tag[MAXN << 2];
    void push_up(int node) {
        min[node] = std::min(min[node << 1], min[node << 1 | 1]);
    }
    void push_down(int node) {
        min[node << 1] += tag[node];
        tag[node << 1] += tag[node];
        min[node << 1 | 1] += tag[node];
        tag[node << 1 | 1] += tag[node];
        tag[node] = 0;
    }
    void build(int node, int L, int R) {
        if (L == R) {
            min[node] = inf;
            return;
        }
        int mid = (L + R) / 2;
        build(node << 1, L, mid);
        build(node << 1 | 1, mid + 1, R);
        push_up(node);
    }
    void add(int node, int L, int R, int l, int r, const int &val) {
        if (l <= L && R <= r) {
            min[node] += val;
            tag[node] += val;
            return;
        }
        push_down(node);
        int mid = (L + R) / 2;
        if (l <= mid) add(node << 1, L, mid, l, r, val);
        if (r > mid) add(node << 1 | 1, mid + 1, R, l, r, val);
        push_up(node);
    }
    ll query(int node, int L, int R, int l, int r) {
        if (l <= L && R <= r) {
            return min[node];
        }
        push_down(node);
        int mid = (L + R) / 2;
        ll res = inf;
        if (l <= mid) res = std::min(res, query(node << 1, L, mid, l, r));
        if (r > mid)
            res = std::min(res, query(node << 1 | 1, mid + 1, R, l, r));
        push_up(node);
        return res;
    }
    void set(int node, int L, int R, int x, const ll &val) {
        if (L == R) {
            min[node] = val;
            return;
        }
        push_down(node);
        int mid = (L + R) / 2;
        if (x <= mid) set(node << 1, L, mid, x, val);
        else set(node << 1 | 1, mid + 1, R, x, val);
        push_up(node);
    }
} tree;

ll f[MAXN];

int main() {
    scanf("%d%d%d", &n, &k, &A);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d%d", &node[i].x, &node[i].y, &node[i].c);
        node[i].x = k - node[i].x;
    }
    std::sort(node + 1, node + 1 + n,
              [](const Node &a, const Node &b) { return a.x < b.x; });

    tree.build(1, 0, k);
    int ptr = 1;
    for (int i = 0; i <= k; ++i) {
        ll sum = 0;
        while (ptr <= n && node[ptr].x == i) {
            sum += node[ptr].c;
            if (node[ptr].y + 1 <= node[ptr].x - 1)
                tree.add(1, 0, k, node[ptr].y + 1, node[ptr].x - 1,
                         node[ptr].c);
            ++ptr;
        }
        ll val = i == 0 ? sum : f[i - 1] - A + sum;
        if (i) val = std::min(val, tree.query(1, 0, k, 0, i - 1));
        val = std::min(val, 0ll);
        f[i] = val;
        tree.set(1, 0, k, i, val);
    }

    printf("%lld\n", tree.query(1, 0, k, k, k) + (ll)k * A);
}