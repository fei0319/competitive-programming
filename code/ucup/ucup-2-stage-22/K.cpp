#include <bits/stdc++.h>

constexpr int MAXS = 6e7;
struct Node {
    int ls, rs;
    int tag;
} tr[MAXS];
int cnt;
int new_node() {
    return ++cnt;
}
int copy(int node) {
    int x = new_node();
    tr[x] = tr[node];
    return x;
}
void clone(int &node, int L, int R, int x, int tag_x, int y, int tag_y, int l,
           int mid, int r) {
    tag_x += tr[x].tag;
    tag_y += tr[y].tag;
    if (l <= L && R <= mid) {
        node = copy(x);
        tr[node].tag = tag_x;
        return;
    }
    if (mid < L && R <= r) {
        node = copy(y);
        tr[node].tag = tag_y;
        return;
    }

    node = new_node();
    int MID = (L + R) / 2;
    clone(tr[node].ls, L, MID, tr[x].ls, tag_x, tr[y].ls, tag_y, l, mid, r);
    clone(tr[node].rs, MID + 1, R, tr[x].rs, tag_x, tr[y].rs, tag_y, l, mid, r);
}
void modify(int &node, int L, int R, int l, int r, const int &val) {
    node = copy(node);
    if (l <= L && R <= r) {
        tr[node].tag += val;
        return;
    }
    int mid = (L + R) / 2;
    if (l <= mid) {
        modify(tr[node].ls, L, mid, l, r, val);
    }
    if (r > mid) {
        modify(tr[node].rs, mid + 1, R, l, r, val);
    }
}
int query(int node, int L, int R, int x) {
    if (!node) {
        return 0;
    }
    if (L == R) {
        return tr[node].tag;
    }
    int mid = (L + R) / 2;
    if (x <= mid) {
        return query(tr[node].ls, L, mid, x) + tr[node].tag;
    } else {
        return query(tr[node].rs, mid + 1, R, x) + tr[node].tag;
    }
}

int main() {
    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }

    std::vector<int> pos(n + 1, n + 1);
    std::vector<int> rt(n + 3);
    rt[n + 1] = new_node();
    for (int i = n; i >= 1; --i) {
        clone(rt[i], 1, n + 1, rt[i + 1], 0, rt[pos[a[i]] + 1], 0, 1, pos[a[i]],
              n + 1);
        modify(rt[i], 1, n + 1, i + 1, pos[a[i]], 1);
        pos[a[i]] = i;
    }

    int lastans = 0;
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        l ^= lastans, r ^= lastans;
        lastans = query(rt[l], 1, n + 1, r + 1);
        std::cout << lastans << '\n';
    }
}
