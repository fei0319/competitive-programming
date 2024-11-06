#include <bits/stdc++.h>

using ll = long long int;

constexpr int MAXN = 1e6 + 19;

int n, q, a[MAXN], pos[MAXN];

struct Node {
    int r, id;
};
ll ans[MAXN];
std::vector<Node> query[MAXN];

struct BIT {
    ll tr[MAXN];
    void update(int x, ll k) {
        for (; x <= n; x += x & -x) {
            tr[x] += k;
        }
    }
    ll query(int x) {
        ll res = 0;
        for (; x; x -= x & -x) {
            res += tr[x];
        }
        return res;
    }
    ll query(int l, int r) { return query(r) - query(l - 1); }
} mt;

bool vist[MAXN];
std::vector<ll> t[MAXN];

void solve() {
    std::cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        pos[a[i]] = i;
    }

    for (int i = 1; i <= n; ++i) {
        query[i].clear();
        t[i].clear();
    }
    std::fill(vist, vist + n + 1, false);
    std::fill(mt.tr, mt.tr + n + 1, 0);

    for (int i = 1; i <= q; ++i) {
        int l, r;
        std::cin >> l >> r;
        query[l].push_back(Node{r, i});
    }

    for (int i = n; i >= 1; --i) {
        vist[a[i]] = true;

        t[a[i]].resize(n / a[i] + 1);
        t[a[i]][1] = 1;
        for (int j = a[i] * 2; j <= n; j += a[i]) {
            if (vist[j]) {
                for (int k = 1; k < t[j].size(); ++k) {
                    t[a[i]][k * j / a[i]] += t[j][k];
                }
            }
        }

        for (int j = 1; j < t[a[i]].size(); ++j) {
            mt.update(pos[j * a[i]], t[a[i]][j]);
        }

        for (auto node : query[i]) {
            ans[node.id] = mt.query(i, node.r);
        }
    }

    for (int i = 1; i <= q; ++i) {
        std::cout << ans[i] << ' ';
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