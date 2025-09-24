#include <bits/stdc++.h>

using i64 = int64_t;
constexpr int S = 1e6;
constexpr i64 INF = 1e18;
struct Node {
    i64 max{-INF};
    i64 tag_max{-INF}, tag_add{0};
};
std::vector<Node> tr;
void push_up(int x) {
    tr[x].max = std::max(tr[x << 1].max, tr[x << 1 | 1].max);
}
void push_down(int x) {
    if (tr[x].tag_max != -INF) {
        i64 &tag_max = tr[x].tag_max;
        tr[x << 1].tag_max = std::max(tr[x << 1].tag_max, tag_max);
        tr[x << 1].max = std::max(tr[x << 1].max, tag_max);
        tr[x << 1 | 1].tag_max = std::max(tr[x << 1 | 1].tag_max, tag_max);
        tr[x << 1 | 1].max = std::max(tr[x << 1 | 1].max, tag_max);
        tag_max = -INF;
    }
    if (tr[x].tag_add != 0) {
        i64 &tag_add = tr[x].tag_add;
        tr[x << 1].tag_add += tag_add;
        tr[x << 1].max += tag_add;
        tr[x << 1 | 1].tag_add += tag_add;
        tr[x << 1 | 1].max += tag_add;
        tag_add = 0;
    }
}
void maxify(int x, int L, int R, int l, int r, i64 v) {
    if (l <= L && R <= r) {
        tr[x].tag_max = std::max(tr[x].tag_max, v);
        tr[x].max = std::max(tr[x].max, v);
        return;
    }

    int mid = L + (R - L) / 2;
    push_down(x);
    if (l <= mid) maxify(x << 1, L, mid, l, r, v);
    if (r > mid) maxify(x << 1 | 1, mid + 1, R, l, r, v);
    push_up(x);
}
void add(int x, int L, int R, int l, int r, i64 v) {
    if (l <= L && R <= r) {
        tr[x].tag_add += v;
        tr[x].max += v;
        return;
    }

    int mid = L + (R - L) / 2;
    push_down(x);
    if (l <= mid) add(x << 1, L, mid, l, r, v);
    if (r > mid) add(x << 1 | 1, mid + 1, R, l, r, v);
    push_up(x);
}
i64 query(int x, int L, int R, int l, int r) {
    if (l <= L && R <= r) return tr[x].max;

    int mid = L + (R - L) / 2;
    i64 res = -INF;
    push_down(x);
    if (l <= mid) res = std::max(res, query(x << 1, L, mid, l, r));
    if (r > mid) res = std::max(res, query(x << 1 | 1, mid + 1, R, l, r));
    push_up(x);
    return res;
}

auto solve() -> void {
    int n;
    std::cin >> n;

    std::vector<int> v(n), a(n), b_pos(n);
    for (int &i : v) std::cin >> i;
    for (int &i : a) {
        std::cin >> i;
        --i;
    }
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        b_pos[x - 1] = i;
    }

    const int L = -1, R = n - 1;
    tr.clear();
    tr.resize((R - L + 1) * 4 + 1);
    maxify(1, L, R, -1, -1, 0);

    for (int i = 0; i < n; ++i) {

        const i64 max = query(1, L, R, -1, b_pos[a[i]] - 1);

        add(1, L, R, -1, b_pos[a[i]] - 1, v[a[i]]);
        // std::cout << std::format("Add {} {} {}\n", -1, b_pos[a[i]] - 1,
        //                          v[a[i]]);
        // for (int j = L; j <= R; ++j) {
        //     std::cout << query(1, L, R, j, j) << ' ';
        // }
        // std::cout << '\n';

        maxify(1, L, R, b_pos[a[i]], b_pos[a[i]], max);
        // std::cout << std::format("Maxify {} {} {}\n", b_pos[a[i]],
        //                          b_pos[a[i]], max);

        // for (int j = L; j <= R; ++j) {
        //     std::cout << query(1, L, R, j, j) << ' ';
        // }
        // std::cout << '\n';
    }

    std::cout << query(1, L, R, L, R) << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    for (auto _ : std::views::iota(0, t)) solve();
}
