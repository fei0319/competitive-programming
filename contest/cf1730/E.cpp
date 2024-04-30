#include <bits/stdc++.h>

#include <ranges>

using ll = long long int;

constexpr int MAXN = 1e6 + 19;
constexpr int N = 1e6;

int n, a[MAXN];
std::vector<int> divisors[MAXN];

namespace Segment {
    struct Node {
        std::pair<int, int> val;
    } tr[MAXN << 2];
    void build(int node, int L, int R) {
        if (L == R) {
            tr[node].val = {a[L], L};
            return;
        }
        int mid = (L + R) / 2;
        build(node << 1, L, mid);
        build(node << 1 | 1, mid + 1, R);
        tr[node].val = std::max(tr[node << 1].val, tr[node << 1 | 1].val);
    }
    std::pair<int, int> query(int node, int L, int R, int l, int r) {
        if (l <= L && R <= r) {
            return tr[node].val;
        }
        int mid = (L + R) / 2;
        std::pair<int, int> res{};
        if (l <= mid)
            res = std::max(res, query(node << 1, L, mid, l, r));
        if (r > mid)
            res = std::max(res, query(node << 1 | 1, mid + 1, R, l, r));
        return res;
    }
} // namespace Segment

int l[MAXN], r[MAXN];
void solve(int L, int R) {
    if (L > R) {
        return;
    }
    if (L == R) {
        l[L] = r[L] = L;
        return;
    }
    int mid = Segment::query(1, 1, n, L, R).second;
    l[mid] = L, r[mid] = R;
    solve(L, mid - 1);
    solve(mid + 1, R);
}

struct Revertable {
    int st[MAXN], sz{0};
    int pos[MAXN];
    std::vector<std::vector<std::pair<bool, int>>> op;
    void _push(int x) {
        st[++sz] = x;
        pos[a[x]] = sz;
    }
    void _pop() {
        pos[a[st[sz]]] = 0;
        --sz;
    }
    int index_of(int x) const {
        return pos[x];
    }
    int size() const {
        return sz;
    }
    int top() const {
        return st[sz];
    }
    void record() {
        op.push_back({});
    }
    void revert() {
        auto &p = op.back();
        for (auto &i : std::ranges::reverse_view(p)) {
            if (i.first) {
                _push(i.second);
            } else {
                _pop();
            }
        }
        op.pop_back();
    }
    void push(int x) {
        op.back().emplace_back(false, 0);
        _push(x);
    }
    void pop() {
        op.back().emplace_back(true, st[sz]);
        _pop();
    }
    void clear() {
        while (sz) {
            _pop();
        }
        op.clear();
    }
} L, R;

void solve() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }

    Segment::build(1, 1, n);
    solve(1, n);

    L.st[0] = 0;
    R.st[0] = n + 1;
    for (int i = n; i >= 1; --i) {
        R.record();
        while (R.size() && a[i] <= a[R.top()]) {
            R.pop();
        }
        R.push(i);
    }
    L.record();

    auto proj = [](int x) { return a[x]; };

    ll ans{0};
    for (int i = 1; i <= n; ++i) {
        while (L.size() && a[i] <= a[L.top()]) {
            L.pop();
        }
        L.push(i);

        for (int d : divisors[a[i]]) {
            ll res_l = 0, res_r = 0;
            int len_l = 0, len_r = 0;
            if (L.index_of(d)) {
                len_l = L.st[L.index_of(d)] -
                        std::max(L.st[L.index_of(d) - 1], l[i] - 1);
                len_l = std::max(len_l, 0);
                if (len_l)
                    res_l +=
                        (ll)len_l * (std::min(*(std::ranges::upper_bound(
                                                    R.st + 1, R.st + 1 + R.sz,
                                                    d, {}, proj) -
                                                1),
                                              r[i] + 1) -
                                     i);
            }
            if (R.index_of(d)) {
                len_r = std::min(R.st[R.index_of(d) - 1], r[i] + 1) -
                        R.st[R.index_of(d)];
                len_r = std::max(len_r, 0);
                if (len_r)
                    res_r += (ll)len_r *
                             (i - std::max(*(std::ranges::upper_bound(
                                                 L.st + 1, L.st + 1 + L.sz, d,
                                                 {}, proj) -
                                             1),
                                           l[i] - 1));
            }
            if (len_l && len_r) {
                ans += (ll)len_l * len_r;
            }
            ans += res_l;
            ans += res_r;
            // std::cout << std::format("a[{}]={} d={} len_l={} len_r={}
            // res_l={} res_r={}\n", i, a[i], d, len_l, len_r, res_l, res_r);
        }

        R.revert();
    }

    std::cout << std::format("{}\n", ans);
    L.clear();
    R.clear();
}

int main() {
    for (int i = 1; i <= N; ++i) {
        for (int j = i; j <= N; j += i) {
            divisors[j].push_back(i);
        }
        std::reverse(divisors[i].begin(), divisors[i].end());
    }

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}