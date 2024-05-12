#include <bits/stdc++.h>

using ll = long long int;

constexpr int B = 18;
constexpr int MAXN = 2e5 + 19;
constexpr int INF = 1e9;

int n, p[MAXN], pos[MAXN];

std::vector<std::pair<int, int>> ranges;
ll calc() {
    std::vector<int> max(n + 1, 1);

    for (auto [l, r] : ranges) {
        max[r] = std::max(max[r], l + 1);
    }

    ll res = 0;
    for (int i = 1; i <= n; ++i) {
        max[i] = std::max(max[i], max[i - 1]);
        res += i - max[i] + 1;
    }
    return res;
}

struct Segment {
    int tr[MAXN << 2];
    void modify(int node, int L, int R, int x, const int &val) {
        tr[node] = std::max(tr[node], val);
        if (L == R) {
            return;
        }
        int mid = (L + R) / 2;
        if (x <= mid) {
            modify(node << 1, L, mid, x, val);
        } else {
            modify(node << 1 | 1, mid + 1, R, x, val);
        }
    }
    int find(int node, int L, int R, int l, int r, const int &val) {
        if (L == R) {
            if (tr[node] > val) {
                return L;
            } else {
                return -1;
            }
        }
        int mid = (L + R) / 2;
        if (l <= L && R <= r) {
            if (tr[node] > val) {
                if (int x = find(node << 1, L, mid, l, r, val); x != -1) {
                    return x;
                } else {
                    return find(node << 1 | 1, mid + 1, R, l, r, val);
                }
            }
            return -1;
        }

        if (l <= mid) {
            int x = find(node << 1, L, mid, l, r, val);
            if (x != -1) {
                return x;
            }
        }
        if (r > mid) {
            return find(node << 1 | 1, mid + 1, R, l, r, val);
        }
        return -1;
    }
    int query(int node, int L, int R, int l, int r) {
        if (l <= L && R <= r) {
            return tr[node];
        }
        int mid = (L + R) / 2;
        int res = 0;
        if (l <= mid) {
            res = std::max(res, query(node << 1, L, mid, l, r));
        }
        if (r > mid) {
            res = std::max(res, query(node << 1 | 1, mid + 1, R, l, r));
        }
        return res;
    }
    void clear() {
        std::fill(tr, tr + n * 4 + 1, 0);
    }
} st1, st2;

struct BIT {
    int tr[MAXN];
    void update(int x, int k) {
        for (; x <= n; x += x & -x) {
            tr[x] += k;
        }
    }
    int query(int x) {
        int res = 0;
        for (; x; x -= x & -x) {
            res += tr[x];
        }
        return res;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
    void clear() {
        std::fill(tr, tr + n + 1, 0);
    }
} bt;

void work(bool reverse) {
    st1.clear();
    for (int i = 1; i <= n; ++i) {
        st1.modify(1, 1, n, i, p[i]);
    }
    st2.clear();
    bt.clear();

    auto find = [&](int L, int R) -> int {
        if (st2.query(1, 1, n, L, R) >= L) {
            int l = L, r = R;
            while (l < r) {
                int mid = (l + r) / 2;
                if (st2.query(1, 1, n, L, mid) >= L) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            return l;
        }
        return -1;
    };

    for (int i = 1; i <= n; ++i) {
        int first_great = 0;
        if (pos[i] + 1 <= n && st1.query(1, 1, n, pos[i] + 1, n) > i) {
            first_great = st1.find(1, 1, n, pos[i] + 1, n, i);
        }

        if (first_great) {
            int x = find(first_great + 1, n);
            if (x != -1) {
                if (!reverse) {
                    ranges.emplace_back(pos[i], x);
                } else {
                    ranges.emplace_back(n - x + 1, n - pos[i] + 1);
                }
            }
        }

        if (bt.query(pos[i] - 1)) {
            int x = 0, res = 0, target = bt.query(pos[i] - 1);
            for (int b = B; b >= 0; --b) {
                if (x + (1 << b) <= n && res + bt.tr[x + (1 << b)] < target) {
                    x += 1 << b;
                    res += bt.tr[x];
                }
            }
            st2.modify(1, 1, n, pos[i], x + 1);
        }
        bt.update(pos[i], 1);
    }
}

constexpr bool input = true;

void solve() {
    if (input) {
        std::cin >> n;
        for (int i = 1; i <= n; ++i) {
            std::cin >> p[i];
        }
    } else {
        n = 2e5;
        std::iota(p + 1, p + 1 + n, 1);

        std::mt19937 rng(time(nullptr));
        std::shuffle(p + 1, p + 1 + n, rng);
    }

    for (int i = 1; i <= n; ++i) {
        pos[p[i]] = i;
    }

    work(false);
    std::reverse(p + 1, p + n + 1);
    for (int i = 1; i <= n; ++i) {
        pos[p[i]] = i;
    }
    work(true);

    std::cout << calc() << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T = 1;

    while (T--) {
        solve();
    }

    return 0;
}