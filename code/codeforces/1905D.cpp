#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 1e6 + 19;

class Segment {
    struct Node {
        ll sum{0LL};
        int cnt{0};
        bool tag{false};
    };
    static Node tr[MAXN << 2];
    void push_down(int node) {
        if (tr[node].tag) {
            tr[node << 1].sum = tr[node << 1].cnt = 0;
            tr[node << 1].tag = true;
            tr[node << 1 | 1] = tr[node << 1];
            tr[node].tag = false;
        }
    }
    void push_up(int node) {
        tr[node].sum = tr[node << 1].sum + tr[node << 1 | 1].sum;
        tr[node].cnt = tr[node << 1].cnt + tr[node << 1 | 1].cnt;
    }
    void modify(int node, int L, int R, int x, const int &val) {
        tr[node].sum += (ll)x * val;
        tr[node].cnt += val;
        if (L == R) return;
        push_down(node);
        int mid = (L + R) / 2;
        if (x <= mid) modify(node << 1, L, mid, x, val);
        else modify(node << 1 | 1, mid + 1, R, x, val);
        push_up(node);
    }
    void clear(int node, int L, int R, int l, int r) {
        if (l <= L && R <= r) {
            tr[node].sum = tr[node].cnt = 0;
            tr[node].tag = true;
            return;
        }
        push_down(node);
        int mid = (L + R) / 2;
        if (l <= mid) clear(node << 1, L, mid, l, r);
        if (r > mid) clear(node << 1 | 1, mid + 1, R, l, r);
        push_up(node);
    }
    int query(int node, int L, int R, int l, int r) {
        if (l <= L && R <= r) return tr[node].cnt;
        push_down(node);
        int mid = (L + R) / 2;
        int res = 0;
        if (l <= mid) res += query(node << 1, L, mid, l, r);
        if (r > mid) res += query(node << 1 | 1, mid + 1, R, l, r);
        push_up(node);
        return res;
    }
    ll get_sum(int node) { return tr[node].sum; }
    int L, R;

public:
    explicit Segment(int L, int R) : L(L), R(R) {}
    void modify(int x, const int &val) { modify(1, L, R, x, val); }
    void clear(int l, int r) { clear(1, L, R, l, r); }
    int query(int l, int r) { return query(1, L, R, l, r); }
    ll get_sum() { return get_sum(1); }
};

using sg = Segment;
sg::Node sg::tr[MAXN << 2];

void solve(void) {
    int n;
    std::cin >> n;

    std::vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> p[i];
    }

    std::vector<ll> suf(n + 1), pre(n + 1);

    Segment mt{0, n};
    mt.clear(0, n);

    for (int i = 1; i <= n; ++i) {
        int num = mt.query(p[i] + 1, n);
        mt.clear(p[i] + 1, n);
        mt.modify(p[i], num);

        mt.modify(n, 1);
        pre[i] = mt.get_sum();
    }

    for (int i = 1; i <= n; ++i) {
        suf[i] = mt.get_sum();

        int num = mt.query(p[i] + 1, n);
        mt.clear(p[i] + 1, n);
        mt.modify(p[i], num);
    }

    ll ans = pre[n];
    for (int i = 1; i < n; ++i) {
        ans = std::max(ans, pre[i] + suf[i + 1]);
    }
    std::cout << ans << '\n';
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}