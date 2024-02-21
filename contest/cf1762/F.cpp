#include <bits/stdc++.h>

using ll = long long int;

const int INF = 1e9;
const int MAXN = 5e5 + 19, MAXS = 1e7;

class Segment {
    static struct Node {
        int ls, rs;
        int sum;
    } tr[MAXS];
    static int tot;
    static void modify(int &node, int L, int R, int l, int r, const int &val) {
        if (!node) {
            node = ++tot;
        }
        if (l <= L && R <= r) {
            tr[node].sum += val;
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
    static int query(int node, int L, int R, int x) {
        if (!node) {
            return 0;
        }
        if (L == R) {
            return tr[node].sum;
        }
        int mid = (L + R) / 2;
        if (x <= mid) {
            return tr[node].sum + query(tr[node].ls, L, mid, x);
        } else {
            return tr[node].sum + query(tr[node].rs, mid + 1, R, x);
        }
    }
    static const int L = 0, R = 1e5;
public:
    static void clear() {
        while (tot) {
            tr[tot--] = Node {0, 0, 0};
        }
    }
    static void modify(int &rt, int l, int r, const int &val) {
        if (l > r) return;
        modify(rt, L, R, l, r, val);
    }
    static int query(int rt, int x) {
        return query(rt, L, R, x);
    }
};
Segment::Node Segment::tr[MAXS];
int Segment::tot;
using sg = Segment;

int n, k, a[MAXN];
int cnt[MAXN];

void solve() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }

    int rt = 0;
    sg::clear();

    ll ans = 0;
    std::set<std::pair<int, int>> sl, sr;
    for (int i = 1; i <= n; ++i) {
        {
            int sz = 1;
            auto begin = sl.lower_bound({a[i] - k, 0}), end = sl.upper_bound({a[i], INF});
            std::vector<std::pair<int, int>> pre(begin, end);
            for (auto [v, s] : pre) {
                sl.erase({v, s});
                sg::modify(rt, v, v + k, -s);
                sg::modify(rt, v, a[i] - 1, s);
                sz += s;
            }
            sg::modify(rt, a[i], a[i] + k, sz);
            sl.emplace(a[i], sz);
        }
        {
            int sz = 1;
            auto begin = sr.lower_bound({a[i], 0}), end = sr.upper_bound({a[i] + k, INF});
            std::vector<std::pair<int, int>> pre(begin, end);
            for (auto [v, s] : pre) {
                sr.erase({v, s});
                sg::modify(rt, v - k, v, -s);
                sg::modify(rt, a[i] + 1, v, s);
                sz += s;
            }
            sg::modify(rt, a[i] - k, a[i], sz);
            sr.emplace(a[i], sz);
        }
        ans += sg::query(rt, a[i]);
    }

    for (int i = 1; i <= n; ++i) {
        cnt[a[i]] += 1;
        ans -= cnt[a[i]];
    }
    for (int i = 1; i <= n; ++i) {
        cnt[a[i]] -= 1;
    }

    std::cout << ans << '\n';
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