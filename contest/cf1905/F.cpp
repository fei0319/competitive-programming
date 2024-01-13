#include <bits/stdc++.h>

using ll = long long int;

const int MAXS = 1e7;

struct Node {
    int ls, rs;
    int num;
};
Node tr[MAXS];

class PersistantSegment {
    static int ind;
    static int new_node() {
        tr[++ind].num = 0;
        return ind;
    }

public:
    static void clear() {
        ind = 0;
    }
    static int copy(int node) {
        int res = new_node();
        tr[res] = tr[node];
        return res;
    }
    static void modify(int node, int L, int R, int x, const int &val) {
        tr[node].num += val;
        if (L == R) {
            return;
        }
        int mid = (L + R) / 2;
        if (x <= mid)
            modify(tr[node].ls = copy(tr[node].ls), L, mid, x, val);
        else
            modify(tr[node].rs = copy(tr[node].rs), mid + 1, R, x, val);
    }
    static int query(int node, int L, int R, int l, int r) {
        if (l <= L && R <= r)
            return tr[node].num;
        int res = 0;
        int mid = (L + R) / 2;
        if (l <= mid)
            res += query(tr[node].ls, L, mid, l, r);
        if (r > mid)
            res += query(tr[node].rs, mid + 1, R, l, r);
        return res;
    }
    static int find(int node, int L, int R) {
        if (L == R)
            return L;
        int mid = (L + R) / 2;
        if (tr[tr[node].ls].num)
            return find(tr[node].ls, L, mid);
        else
            return find(tr[node].rs, mid + 1, R);
    }
    static int find(int node, int L, int R, int l, int r) {
        if (l <= L && R <= r) {
            if (tr[node].num)
                return find(node, L, R);
            else
                return 0;
        }
        int mid = (L + R) / 2;
        if (l <= mid) {
            int t = find(tr[node].ls, L, mid, l, r);
            if (t)
                return t;
        }
        return find(tr[node].rs, mid + 1, R, l, r);
    }
};
int PersistantSegment::ind = 0;

using ps = PersistantSegment;

template <typename T1, typename T2>
struct std::hash<std::pair<T1, T2>> {
    std::size_t operator()(const std::pair<T1, T2> &b) const {
        return std::hash<T1>()(b.first) ^
               (std::hash<T2>()(b.second) + std::hash<T1>()(b.first));
    }
};

void solve(void) {
    int n;
    std::cin >> n;

    std::vector<int> p(n + 1), pos(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> p[i];
        pos[p[i]] = i;
    }

    std::vector<int> pre(n + 1), suf(n + 2);
    ps::clear();
    for (int i = 1; i <= n; ++i) {
        pre[i] = ps::copy(pre[i - 1]);
        ps::modify(pre[i], 1, n, p[i], 1);
    }
    for (int i = n; i >= 1; --i) {
        suf[i] = ps::copy(suf[i + 1]);
        ps::modify(suf[i], 1, n, p[i], 1);
    }

    int tot = 0, rt = ps::copy(0);
    std::unordered_map<std::pair<int, int>, int> mt;
    for (int i = 1; i <= n; ++i) {
        if (p[i] == i) {
            int t = ps::query(pre[i], 1, n, 1, i);
            if (t == i - 1) {
                auto [l, r] =
                    std::pair<int, int>{ps::find(pre[i], 1, n, i + 1, n),
                                        ps::find(suf[i], 1, n, 1, i - 1)};
                mt[{pos[l], pos[r]}] += 1;
            } else if (t == i) {
                tot += 1;
                ps::modify(rt, 1, n, i, 1);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (p[i] != i) {
            mt[{std::min(p[i], i), std::max(p[i], i)}] += 0;
        }
    }
    mt[{1, 2}] += 0;

    int ans = 0;
    for (auto [rg, v] : mt) {
        auto [l, r] = rg;
        int res = v + tot - ps::query(rt, 1, n, l, r);
        if (p[r] == l) {
            if (l == 1 || ps::query(pre[l - 1], 1, n, 1, l - 1) == l - 1) {
                res += 1;
            }
        }
        if (p[l] == r) {
            if (r == n || ps::query(suf[r + 1], 1, n, r + 1, n) == n - r) {
                res += 1;
            }
        }
        ans = std::max(ans, res);
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