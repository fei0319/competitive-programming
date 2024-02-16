#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 2e5 + 19, B = 18;

int n, c, a[MAXN];

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
    int kth(int x) {
        int res = 0, now = 0;
        for (int i = B; i >= 0; --i) {
            if (res + (1 << i) <= n && now + tr[res + (1 << i)] < x) {
                res += 1 << i;
                now += tr[res];
            }
        }
        return res + 1;
    }
} mt;

void solve() {
    std::cin >> n >> c;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    std::sort(a + 1, a + 1 + n);
    if (c >= 0) {
        for (int i = 1; i <= n; ++i) {
            std::cout << a[i] << ' ';
        }
        std::cout << '\n';
        return;
    }

    std::reverse(a + 1, a + 1 + n);

    std::fill(mt.tr + 1, mt.tr + 1 + n, 0);
    for (int i = 1; i <= n; ++i) {
        mt.update(i, 1);
    }


    auto calc = [&](int x, int y) {
        if (x < 1 || x > n || y < 1 || y > n) return 0LL;
        return std::abs<ll>((ll)a[y] - a[x] - c);
    };

    std::set<std::pair<ll, int>> s[2];
    auto get_value = [&](int x, int t) {
        int rank = mt.query(x);
        int p = mt.kth(rank - 1), q = mt.kth(rank + 1);
        if (t == 0)
            return calc(p, x) + calc(x, q) - calc(p, q);
        else
            return calc(p, x) + calc(x, q) - calc(p, q) + a[x] * 2;
    };
    for (int i = 2; i < n; ++i) {
        for (int t = 0; t < 2; ++t) {
            s[t].emplace(get_value(i, t), i);
        }
    }

    int prev = 0;
    for (int i = 1; i <= n; ++i) {
        int tot = mt.query(n);

        auto check = [&](int x) -> bool {
        	x = mt.query(x);
        	
            if (x > tot) {
                return false;
            }
            if (x == 1) {
                return true;
            }
            if (x == 2) {
                int p = prev, a = mt.kth(1), b = mt.kth(2), q = mt.kth(3);
                ll u = calc(p, a) + calc(a, b) + calc(b, q);
                ll v = calc(p, b) + calc(b, a) + calc(a, q);
                return u == v;
            }
            int pa = prev, a = mt.kth(1);
            int pb = mt.kth(x - 1), b = mt.kth(x), qb = mt.kth(x + 1);

            ll u = calc(pb, b) + calc(b, qb) - calc(pb, qb) + ::a[b];
            ll v = std::abs<ll>(::a[b] - ll(::a[pa] + c)) + ::a[a] - c - calc(pa, a);
            return u == v;

            // for ::a[b] >= ::a[pa] + c, i.e. b <= [a certain value]
            // min calc(pb, b) + calc(b, qb) - calc(pb, qb)
            // for ::a[b] < ::a[pa] + c
            // min calc(pb, b) + calc(b, qb) - calc(pb, qb) + ::a[b] * 2
            // std::set<std::pair<value, index>>
        };

        int x = mt.kth(1);
        // t0
        if (!s[0].empty()) {
            ll max_v = (--s[0].end())->first;

            int l = 1, r = n;
            while (l < r) {
                int mid = (l + r + 1) / 2;
                if (a[mid] >= a[prev] + c) {
                    l = mid;
                } else {
                    r = mid - 1;
                }
            }
            // b <= l
            auto it = s[0].upper_bound({max_v, l});
            if (it != s[0].begin()) {
                --it;

                if (it->first == max_v && check(it->second)) {
                    x = std::max(x, it->second);
                }
            }
        }
        // t1
        if (!s[1].empty()) {
            auto it = --s[1].end();
            if (check(it->second)) {
                x = std::max(x, it->second);
            }
        }

        if (check(mt.kth(tot))) {
            x = mt.kth(tot);
        }

        int rank = mt.query(x);
        int p = mt.kth(rank - 1), q = mt.kth(rank + 1);
        
        for (int t = 0; t < 2; ++t) {
            if (rank - 1 > 1) {
                s[t].erase({get_value(p, t), p});
            }
            s[t].erase({get_value(x, t), x});
            if (rank + 1 < tot) {
                s[t].erase({get_value(q, t), q});
            }
        }
        mt.update(prev = x, -1);
        for (int t = 0; t < 2; ++t) {
            if (rank - 1 > 1 && rank + 1 <= tot) {
                s[t].emplace(get_value(p, t), p);
            }
            if (rank - 1 >= 1 && rank + 1 < tot) {
                s[t].emplace(get_value(q, t), q);
            }
        }

        std::cout << a[prev] << ' ';
    }
    std::cout << '\n';
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