#include <bits/stdc++.h>

const int MAXN = 3e5 + 19, INF = 1e9;

class Segment {
    struct Node {
        int min, max;
    } tr[MAXN << 2];
    void push_up(int node) {
        tr[node].min = std::min(tr[node << 1].min, tr[node << 1 | 1].min);
        tr[node].max = std::max(tr[node << 1].max, tr[node << 1 | 1].max);
    }
    void build(int node, int L, int R, int *p) {
        if (L == R) {
            tr[node].min = p[L];
            tr[node].max = p[L];
            return;
        }
        int mid = (L + R) / 2;
        build(node << 1, L, mid, p);
        build(node << 1 | 1, mid + 1, R, p);
        push_up(node);
    }
    int query_min(int node, int L, int R, int l, int r) {
        if (l <= L && R <= r) {
            return tr[node].min;
        }
        int mid = (L + R) / 2;
        int res = +INF;
        if (l <= mid)
            res = std::min(res, query_min(node << 1, L, mid, l, r));
        if (r > mid)
            res =
                std::min(res, query_min(node << 1 | 1, mid + 1, R, l, r));
        return res;
    }
    int query_max(int node, int L, int R, int l, int r) {
        if (l <= L && R <= r) {
            return tr[node].max;
        }
        int mid = (L + R) / 2;
        int res = -INF;
        if (l <= mid)
            res = std::max(res, query_max(node << 1, L, mid, l, r));
        if (r > mid)
            res =
                std::max(res, query_max(node << 1 | 1, mid + 1, R, l, r));
        return res;
    }
    int L, R;

public:
    void build(int L, int R, int *p) {
        this->L = L;
        this->R = R;
        build(1, L, R, p);
    }
    int query_min(int l, int r) { return query_min(1, L, R, l, r); }
    int query_max(int l, int r) { return query_max(1, L, R, l, r); }
} mt;

struct Node {
    int lmax, rmin;
    int l, r;
    int id;
};
int ans[MAXN];

int p[MAXN];
void solve(int L, int R, std::vector<Node> a) {
    if (a.empty()) return;

    std::vector<Node> for_l, for_r;
    int n = 0, mid = (L + R) / 2;
    for (int i = 0; i < (int)a.size(); ++i) {
        if (a[i].l <= L && a[i].r >= R) {
            if (a[i].lmax < a[i].rmin) {
                a[n++] = a[i];
            }
        } else {
            if (a[i].l <= mid) {
                Node node = a[i];
                if (a[i].r > mid)
                    node.rmin = mt.query_min(mid + 1, node.r);
                for_l.push_back(node);
            }
            if (a[i].r > mid) {
                Node node = a[i];
                if (a[i].l <= mid) node.lmax = mt.query_max(a[i].l, mid);
                for_r.push_back(node);
            }
        }
    }
    solve(L, mid, std::move(for_l));
    solve(mid + 1, R, std::move(for_r));

    a.resize(n);
    std::erase_if(a, [](const Node &x) { return ans[x.id]; });
    if (a.empty()) return;

    static int pre_max[MAXN], suf_min[MAXN];
    pre_max[L - 1] = -INF, suf_min[R + 1] = +INF;
    for (int i = L; i <= R; ++i) {
        pre_max[i] = std::max(pre_max[i - 1], p[i]);
    }
    for (int i = R; i >= L; --i) {
        suf_min[i] = std::min(suf_min[i + 1], p[i]);
    }

    std::vector<int> pos;
    for (int i = L; i <= R; ++i) {
        if (pre_max[i] < suf_min[i + 1]) {
            pos.push_back(i);
        }
    }

    for (auto q : a) {
        int x, y;
        int l, r;

        l = 0, r = (int)pos.size() - 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (suf_min[pos[mid] + 1] > q.lmax) r = mid;
            else l = mid + 1;
        }
        x = l;
        if (suf_min[pos[x] + 1] <= q.lmax) continue;

        l = 0, r = (int)pos.size() - 1;
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (pre_max[pos[mid]] < q.rmin) l = mid;
            else r = mid - 1;
        }
        y = l;
        if (pre_max[pos[y]] >= q.rmin) continue;

        if (x < y || (x == y && (pos[x] != R || q.r != R))) {
            ans[q.id] = pos[x];
        }
    }
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> p[i];
    mt.build(1, n, p);
    std::cin >> q;
    std::vector<Node> Q;
    for (int i = 1; i <= q; ++i) {
        Node node;
        std::cin >> node.l >> node.r;
        node.id = i;
        node.lmax = -INF, node.rmin = +INF;
        Q.push_back(node);
    }

    solve(1, n, std::move(Q));
    for (int i = 1; i <= q; ++i) {
        std::cout << (ans[i] ? "Yes" : "No") << '\n';
    }

    return 0;
}