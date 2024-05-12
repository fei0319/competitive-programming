// Problem: P5621 [DBOI2019]德丽莎世界第一可爱
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5621
// Memory Limit: 125 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
typedef long long int ll;
template <typename Tp>
void chkmax(Tp &a, const Tp &b) {
    a = std::max(a, b);
}
template <typename Tp>
void chkmin(Tp &a, const Tp &b) {
    a = std::min(a, b);
}

const int maxn = 5e4 + 19;

struct Node {
    ll a, b, c, d, bonus;
    ll val;
} node[maxn];

int n;

struct Tarray {
    ll tr[maxn];
    void update(int x, const ll &val) {
        for (; x <= n; x += x & -x)
            chkmax(tr[x], val);
    }
    ll query(int x) {
        ll res = 0;
        for (; x; x -= x & -x)
            chkmax(res, tr[x]);
        return res;
    }
    void erase(int x) {
        for (; x <= n; x += x & -x)
            tr[x] = 0;
    }
} mt;

const auto cmp1 = [](const Node &x, const Node &y) {
    if (x.a != y.a)
        return x.a < y.a;
    if (x.b != y.b)
        return x.b < y.b;
    if (x.c != y.c)
        return x.c < y.c;
    return x.d < y.d;
};
const auto cmp2 = [](const Node &x, const Node &y) {
    if (x.b != y.b)
        return x.b < y.b;
    if (x.a != y.a)
        return x.a < y.a;
    if (x.c != y.c)
        return x.c < y.c;
    return x.d < y.d;
};
const auto cmp3 = [](const Node &x, const Node &y) {
    if (x.c != y.c)
        return x.c < y.c;
    if (x.a != y.a)
        return x.a < y.a;
    if (x.b != y.b)
        return x.b < y.b;
    return x.d < y.d;
};

void solve2(int l, int r, Node m) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    std::sort(node + l, node + r + 1, cmp2);
    solve2(l, mid, m);
    int pl = l, pr = mid + 1;
    std::sort(node + l, node + mid + 1, cmp3);
    std::sort(node + mid + 1, node + r + 1, cmp3);
    while (pl <= mid || pr <= r) {
        if (pl <= mid && (pr > r || !cmp3(node[pr], node[pl]))) {
            if (!cmp1(m, node[pl]))
                mt.update(node[pl].d, node[pl].val + node[pl].bonus);
            ++pl;
        } else {
            if (!cmp1(node[pr], m))
                chkmax(node[pr].val, mt.query(node[pr].d));
            ++pr;
        }
    }
    for (int i = l; i <= mid; ++i)
        if (!cmp1(m, node[i]))
            mt.erase(node[i].d);
    solve2(mid + 1, r, m);
}

void solve1(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    std::sort(node + l, node + r + 1, cmp1);
    solve1(l, mid);
    solve2(l, r, node[mid]);
    std::sort(node + l, node + r + 1, cmp1);
    solve1(mid + 1, r);
}

void discrimilate(std::vector<ll> &a) {
    std::sort(a.begin(), a.end());
    a.resize(std::unique(a.begin(), a.end()) - a.begin());
}

int main() {
    scanf("%d", &n);
    std::vector<ll> a, b, c, d;
    for (int i = 1; i <= n; ++i) {
        scanf("%lld%lld%lld%lld%lld", &node[i].a, &node[i].b, &node[i].c,
              &node[i].d, &node[i].bonus);
        a.push_back(node[i].a), b.push_back(node[i].b), c.push_back(node[i].c),
            d.push_back(node[i].d);
    }
    discrimilate(a), discrimilate(b), discrimilate(c), discrimilate(d);
    for (int i = 1; i <= n; ++i) {
        node[i].a =
            std::lower_bound(a.begin(), a.end(), node[i].a) - a.begin() + 1;
        node[i].b =
            std::lower_bound(b.begin(), b.end(), node[i].b) - b.begin() + 1;
        node[i].c =
            std::lower_bound(c.begin(), c.end(), node[i].c) - c.begin() + 1;
        node[i].d =
            std::lower_bound(d.begin(), d.end(), node[i].d) - d.begin() + 1;
    }
    solve1(1, n);
    ll ans = 0;
    for (int i = 1; i <= n; ++i)
        chkmax(ans, node[i].val + node[i].bonus);
    printf("%lld\n", ans);
}