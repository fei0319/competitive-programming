// Problem: E. Qpwoeirut and Vertices
// Contest: Codeforces - Codeforces Round #809 (Div. 2)
// URL: https://codeforces.com/contest/1706/problem/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

typedef long long int ll;

template <typename Tp> void chkmax(Tp &a, const Tp &b) { a = std::max(a, b); }
template <typename Tp> void chkmin(Tp &a, const Tp &b) { a = std::min(a, b); }

template <typename Tp> void read(Tp &res) {
    static char ch;
    ch = getchar(), res = 0;
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        res = res * 10 + ch - 48, ch = getchar();
}

const int maxn = 2e5 + 19;

int n, m, q;

struct Node {
    int L, R, mx, mn;
};

struct T {
    Node tr[maxn << 2];
    void build(int node, int L, int R) {
        tr[node].L = L, tr[node].R = R;
        tr[node].mx = tr[node].mn = L;
    }
    void push_up(int node) {
        tr[node].mx = std::max(tr[node << 1].mx, tr[node << 1 | 1].mx);
        tr[node].mn = std::max(tr[node << 1].mn, tr[node << 1 | 1].mn);
    }
    void modify(int node, int x, const int &val) {
        if (tr[node].L == tr[node].R) {
            tr[node].mx = tr[node].mn = val;
            return;
        }
        int mid = (tr[node].L + tr[node].R) >> 1;
        if (x <= mid)
            modify(node << 1, x, val);
        else
            modify(node << 1 | 1, x, val);
        push_up(node);
    }
    int query(int node, int l, int r) {
        if (l <= tr[node].L && tr[node].R <= r)
            return tr[node].mx == tr[node].mn ? tr[node].mx : -1;
        int mid = (tr[node].L + tr[node].R) >> 1, Lv = 0, Rv = 0;
        if (l <= mid)
            Lv = query(node << 1, l, r);
        if (r > mid)
            Rv = query(node << 1 | 1, l, r);
        if (Lv != 0 && Rv != 0 && Lv != Rv)
            return -1;
        if (Lv == -1 || Rv == -1)
            return -1;
        if (Lv == Rv)
            return Lv;
        return Lv + Rv;
    }
} mt;

struct UFS {
    int fa[maxn];
    void mod(int x, int y) {
        fa[x] = y;
        mt.modify(1, x, y);
    }
    int find(int x) {
        if (x != fa[x])
            mod(x, find(fa[x]));
        return fa[x];
    }
    void merge(int x, int y) {
        x = find(x), y = find(y);
        mod(x, y);
    }
    void init(void) {
        for (int i = 1; i <= n; ++i)
            fa[i] = i;
    }
} ufs;

int main() {
    int T;
    read(T);
    while (T--) {
        read(n), read(m), read(q);
        ufs.init(), mt.build;
        for (int i = 1; i <= n; ++i)
    }
}

/*





















*/