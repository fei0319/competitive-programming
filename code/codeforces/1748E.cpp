#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19, mod = 1e9 + 7;

int n, m, a[maxn];

struct SegmentTree {
    int tr[maxn << 2];
    void push_up(int node) {
        if (a[tr[node << 1]] >= a[tr[node << 1 | 1]])
            tr[node] = tr[node << 1];
        else tr[node] = tr[node << 1 | 1];
    }
    void build(int node, int L, int R) {
        if (L == R) {
            tr[node] = L;
            return;
        }
        int mid = (L + R) >> 1;
        build(node << 1, L, mid), build(node << 1 | 1, mid + 1, R);
        push_up(node);
    }
    int query(int node, int L, int R, int l, int r) {
        if (l <= L && R <= r) return tr[node];
        int mid = (L + R) >> 1;
        if (r <= mid) return query(node << 1, L, mid, l, r);
        if (l > mid) return query(node << 1 | 1, mid + 1, R, l, r);
        int res_l = query(node << 1, L, mid, l, r),
            res_r = query(node << 1 | 1, mid + 1, R, l, r);
        if (a[res_l] >= a[res_r]) return res_l;
        else return res_r;
    }
} mt;

std::vector<int> dfs(int l, int r) {
    if (l > r) return std::vector<int>(m + 1, 1);
    int mid = mt.query(1, 1, n, l, r);
    auto L = dfs(l, mid - 1), R = dfs(mid + 1, r);
    std::vector<int> res(m + 1);
    for (int i = 1; i <= m; ++i) {
        res[i] = res[i - 1];
        res[i] = (res[i] + (ll)L[i - 1] * R[i]) % mod;
    }
    return res;
}

void solve(void) {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }

    mt.build(1, 1, n);
    std::cout << dfs(1, n)[m] << std::endl;
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