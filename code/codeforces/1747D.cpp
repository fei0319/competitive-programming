#pragma GCC optimize(2)
#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

int n, q, a[maxn], ans[maxn];
std::vector<int> pos[maxn], num;

struct Node {
    int l, r, id;
} node[maxn];

struct Tar {
    int tr[maxn];
    void update(int x, int k) {
        for (; x <= n; x += x & -x)
            tr[x] += k;
    }
    int query(int x) {
        int res = 0;
        for (; x; x -= x & -x)
            res += tr[x];
        return res;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
    int find_next(int x) {
        int res = 0, tmp = 0, s = query(x);
        for (int i = 19; ~i; --i) {
            int n_res = res + (1 << i);
            if (n_res > n)
                continue;
            int n_tmp = tmp + tr[n_res];
            if (n_tmp >= n_res - x + s) {
                res = n_res, tmp = n_tmp;
            }
        }
        return res + 1;
    }
} mt[3];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        a[i] ^= a[i - 1];
    }
    for (int i = 1; i <= q; ++i) {
        std::cin >> node[i].l >> node[i].r;
        node[i].id = i;
    }
    std::sort(node + 1, node + 1 + q, [](const Node &x, const Node &y) {
        return a[x.l - 1] < a[y.l - 1];
    });

    for (int i = 0; i <= n; ++i) {
        num.push_back(a[i]);
    }
    std::sort(num.begin(), num.end());
    num.resize(std::unique(num.begin(), num.end()) - num.begin());

    for (int i = 1; i <= n; ++i) {
        pos[std::lower_bound(num.begin(), num.end(), a[i]) - num.begin()]
            .push_back(i);
    }

    for (int l = 1, r; l <= q; l = r + 1) {
        int x = a[node[l].l - 1],
            p = std::lower_bound(num.begin(), num.end(), x) - num.begin();
        r = l;
        while (r + 1 <= q && a[node[r + 1].l - 1] == x) {
            ++r;
        }

        for (int i : pos[p]) {
            mt[i & 1].update(i, 1);
            mt[2].update(i, 1);
        }

        for (int i = l; i <= r; ++i) {
            int L = node[i].l, R = node[i].r, id = node[i].id, preL = L;
            if (a[R] != x) {
                ans[id] = -1;
                continue;
            }
            if (a[L] == x) {
                L = mt[2].find_next(L);
            }
            if (L >= R) {
                ans[id] = 0;
            } else if (L != preL || (R - L) % 2 == 0 || (R - preL) % 2 == 0) {
                ans[id] = 1;
            } else {
                if (mt[0].query(L, R) == 0 || mt[1].query(L, R) == 0) {
                    ans[id] = -1;
                } else {
                    if (a[R - 1] == x) {
                        ans[id] = 1;
                    } else {
                        ans[id] = 2;
                    }
                }
            }
        }

        for (int i : pos[p]) {
            mt[i & 1].update(i, -1);
            mt[2].update(i, -1);
        }
    }

    for (int i = 1; i <= q; ++i) {
        std::cout << ans[i] << std::endl;
    }

    return 0;
}