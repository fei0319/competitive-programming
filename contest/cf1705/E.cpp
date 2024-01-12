// Problem: E. Mark and Professor Koro
// Contest: Codeforces - Codeforces Round #807 (Div. 2)
// URL: https://codeforces.com/contest/1705/problem/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

typedef long long int ll;

template <typename Tp>
void chkmax(Tp &a, const Tp &b) {
    a = std::max(a, b);
}
template <typename Tp>
void chkmin(Tp &a, const Tp &b) {
    a = std::min(a, b);
}

template <typename Tp>
void read(Tp &res) {
    static char ch;
    ch = getchar(), res = 0;
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        res = res * 10 + ch - 48, ch = getchar();
}

const int maxn = 2e5 + 19;

int n, q, a[maxn];

struct Node {
    int l, r, cnt, tag;
} t[maxn << 3];

void push_up(int node) {
    t[node].cnt = t[node << 1].cnt + t[node << 1 | 1].cnt;
}

void push_down(int node) {
    if (t[node].tag != -1) {
        t[node << 1].cnt = t[node].tag * (t[node << 1].r - t[node << 1].l + 1);
        t[node << 1 | 1].cnt =
            t[node].tag * (t[node << 1 | 1].r - t[node << 1 | 1].l + 1);

        t[node << 1].tag = t[node].tag;
        t[node << 1 | 1].tag = t[node].tag;

        t[node].tag = -1;
    }
}

void build(int node, int L, int R) {
    t[node].l = L;
    t[node].r = R;
    t[node].tag = -1;
    if (L == R) {
        t[node].cnt = 0;
        return;
    }
    int mid = (L + R) >> 1;
    build(node << 1, L, mid), build(node << 1 | 1, mid + 1, R);
    push_up(node);
}

int toppos(int node) {
    if (t[node].l == t[node].r)
        return t[node].l;
    push_down(node);
    if (t[node << 1 | 1].cnt)
        return toppos(node << 1 | 1);
    return toppos(node << 1);
}

int query(int node, int L, int R) {
    if (L <= t[node].l && t[node].r <= R)
        return t[node].cnt;
    push_down(node);
    int mid = (t[node].l + t[node].r) >> 1, res = 0;
    if (L <= mid)
        res += query(node << 1, L, R);
    if (R > mid)
        res += query(node << 1 | 1, L, R);
    push_up(node);
    return res;
}

void modify(int node, int L, int R, int tag) {
    if (L <= t[node].l && t[node].r <= R) {
        t[node].tag = tag, t[node].cnt = tag * (t[node].r - t[node].l + 1);
        return;
    }
    push_down(node);
    int mid = (t[node].l + t[node].r) >> 1;
    if (L <= mid)
        modify(node << 1, L, R, tag);
    if (R > mid)
        modify(node << 1 | 1, L, R, tag);
    push_up(node);
}

void insert(int a) {
    if (query(1, a, a) == 0)
        return modify(1, a, a, 1);
    int l = a, r = t[1].r;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (query(1, a, mid) == mid - a + 1)
            l = mid;
        else
            r = mid - 1;
    }
    modify(1, a, l, 0);
    modify(1, l + 1, l + 1, 1);
}

void erase(int a) {
    if (query(1, a, a) == 1)
        return modify(1, a, a, 0);
    int l = a, r = t[1].r;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (query(1, a, mid) == 0)
            l = mid;
        else
            r = mid - 1;
    }
    modify(1, a, l, 1);
    modify(1, l + 1, l + 1, 0);
}

int main() {
    read(n), read(q);
    build(1, 1, 2e5 + 100);
    for (int i = 1; i <= n; ++i) {
        read(a[i]);
        insert(a[i]);
    }
    while (q--) {
        int x, k;
        read(x), read(k);
        erase(a[x]);
        insert(a[x] = k);
        printf("%d\n", toppos(1));
    }
}

/*





















*/