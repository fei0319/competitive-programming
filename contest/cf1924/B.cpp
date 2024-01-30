#include <bits/stdc++.h>

using ll = long long int;
const int MAXN = 3e5 + 19;

int n, m, q;

struct BIT {
    ll tr[MAXN];
    void update(int x, ll k) {
        for (; x <= n; x += x & -x) {
            tr[x] += k;
        }
    }
    ll query(int x) {
        ll res = 0;
        for (; x; x -= x & -x) res += tr[x];
        return res;
    }
} num, val;

ll sum(int x) {
	if (x <= 0) return 0;
    return (ll)x * (x + 1) / 2;
}

int prev(int x) {
    int v = num.query(x);
    int l = 1, r = x;
    while (l < r) {
        int mid = (l + r) / 2;
        if (num.query(mid) >= v) r = mid;
        else l = mid + 1;
    }
    return l;
}
int next(int x) {
    int v = num.query(x - 1);
    int l = x - 1, r = n;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (num.query(mid) <= v) l = mid;
        else r = mid - 1;
    }
    return l + 1;
}

int V[MAXN];
void add(int x, int v) {
    int pre = prev(x), nxt = next(x);
    num.update(x, 1);
    val.update(x, v * sum(nxt - x - 1));

    val.update(pre, -V[pre] * sum(nxt - pre - 1));
    val.update(pre, V[pre] * sum(x - pre - 1));

    V[x] = v;
}

ll query(int l, int r) {
    ll res = 0;
    if (prev(l) == prev(r)) {
        int nxt = next(r), pre = prev(l);
        if (l == pre) l += 1;
        if (r == nxt) r -= 1;
        if (l > r) return 0;
        return (sum(nxt - l) - sum(nxt - r - 1)) * V[pre];
    }
    int L = next(l), R = prev(r);
    res += val.query(R - 1) - val.query(L - 1);
    
    res += sum(L - l) * V[prev(l)];
    
    res += (sum(next(r) - R - 1) - sum(next(r) - r - 1)) * V[R];
    
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);


    std::cin >> n >> m >> q;

    std::vector<std::pair<int, int>> h(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> h[i].first;
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> h[i].second;
    }
    std::sort(h.begin(), h.end());

    for (int i = 0; i < m; ++i) {
        num.update(h[i].first, 1);
        if (i + 1 < m) {
            val.update(h[i].first, h[i].second * sum(h[i + 1].first - h[i].first - 1));
        }
        V[h[i].first] = h[i].second;
    }

    while (q--) {
        int t;
        std::cin >> t;
        if (t == 1) {
            int x, v;
            std::cin >> x >> v;
            add(x, v);
        } else {
            int l, r;
            std::cin >> l >> r;
            std::cout << query(l, r) << '\n';
        }
    }

    return 0;
}