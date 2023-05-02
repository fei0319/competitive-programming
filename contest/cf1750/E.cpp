#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e6 + 19;

void get_prefix(int *s, int n) {
    static char str[maxn];
    std::cin >> (str + 2);
    s[1] = 0;
    for (int i = 2; i <= n + 1; ++i) {
        s[i] = s[i - 1] + (str[i] == '(' ? 1 : -1);
    }
}

int n, s[maxn];
int max[maxn], min[maxn];
int st[maxn], top;

struct SegmentTree {
    ll sum[maxn << 1], tag[maxn << 1];
    static const int NOTAG = 1e9;
    void build(int node, int l, int r) {
        sum[node] = 0, tag[node] = NOTAG;
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        build(node << 1, l, mid), build(node << 1 | 1, mid + 1, r);
    }
    void push_up(int node) { sum[node] = sum[node << 1] + sum[node << 1 | 1]; }
    void push_down(int node, int L, int R) {
        if (tag[node] == NOTAG) {
            return;
        }
        if (L != R) {
            int mid = (L + R) >> 1;
            sum[node << 1] = tag[node] * (mid - L + 1);
            tag[node << 1] = tag[node];
            sum[node << 1 | 1] = tag[node] * (R - mid);
            tag[node << 1 | 1] = tag[node];
        }
        tag[node] = NOTAG;
    }
    void modify(int node, int L, int R, int l, int r, const ll &val) {
        if (l <= L && R <= r) {
            sum[node] = val * (R - L + 1);
            tag[node] = val;
            return;
        }
        push_down(node, L, R);
        int mid = (L + R) >> 1;
        if (l <= mid)
            modify(node << 1, L, mid, l, r, val);
        if (r > mid)
            modify(node << 1 | 1, mid + 1, R, l, r, val);
        push_up(node);
    }
    ll query(int node, int L, int R, int l, int r) {
        if (l <= L && R <= r) {
            return sum[node];
        }
        push_down(node, L, R);
        ll res = 0ll;
        int mid = (L + R) >> 1;
        if (l <= mid)
            res += query(node << 1, L, mid, l, r);
        if (r > mid)
            res += query(node << 1 | 1, mid + 1, R, l, r);
        push_up(node);
        return res;
    }
} mt;

void solve(void) {
    std::cin >> n;
    get_prefix(s, n), ++n;

    ll ans = 0ll;
    mt.build(1, 1, n), top = 0;
    for (int i = 1; i <= n; ++i) {
        while (top && s[st[top]] >= s[i]) {
            --top;
        }
        mt.modify(1, 1, n, st[top] + 1, i, s[i]);
        ans -= mt.query(1, 1, n, 1, i);
        st[++top] = i;
    }
    std::sort(s + 1, s + 1 + n);
    for (int i = 1; i <= n; ++i) {
        ans += (ll)s[i] * i;
    }
    std::cout << ans << std::endl;
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