#include <bits/stdc++.h>

int gc() {
    static char buf[1 << 16];
    static int bc, be;
    if (bc >= be)
        buf[bc = 0] = EOF, be = fread(buf, 1, sizeof(buf), stdin);
    return buf[bc++];
}
int read() {
    int res = 0, c = gc();
    while (!isdigit(c)) c = gc();
    while (isdigit(c)) res = res * 10 + c - 48, c = gc();
    return res;
}
void write(int x) {
    if (x < 0) x = -x, putchar('-');
    if (x >= 10) write(x / 10);
    putchar('0' + x % 10);
}

constexpr int MAXS = 1e6 + 19;

struct Node {
    int ls, rs;
    int val, sz;
    uint32_t pri;
} tr[MAXS];
int tot;
std::mt19937
    rng(std::chrono::steady_clock::now().time_since_epoch().count());
int new_node(int v) {
    ++tot;
    tr[tot].val = v, tr[tot].sz = 1;
    tr[tot].pri = rng();
    return tot;
}
void push_up(int x) { tr[x].sz = tr[tr[x].ls].sz + tr[tr[x].rs].sz + 1; }

int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (tr[x].pri > tr[y].pri) {
        return tr[x].rs = merge(tr[x].rs, y), push_up(x), x;
    } else {
        return tr[y].ls = merge(x, tr[y].ls), push_up(y), y;
    }
}
// [<=v], [>v]
std::pair<int, int> split(int x, int v) {
    if (!x) return {0, 0};
    if (tr[x].val <= v) {
        auto [l, r] = split(tr[x].rs, v);
        tr[x].rs = l, push_up(x);
        return {x, r};
    } else {
        auto [l, r] = split(tr[x].ls, v);
        tr[x].ls = r, push_up(x);
        return {l, x};
    }
}
void insert(int &rt, int v) {
    auto [mr, r] = split(rt, v);
    auto [l, ml] = split(mr, v - 1);
    if (!ml) ml = new_node(v);
    rt = merge(merge(l, ml), r);
}
void erase(int &rt, int v) {
    auto [mr, r] = split(rt, v);
    auto [l, ml] = split(mr, v - 1);
    rt = merge(l, r);
}
int kth(int &rt, int k) {
    if (k > tr[rt].sz) return -1;
    int x = rt;
    while (true) {
        int lsz = tr[tr[x].ls].sz;
        if (k <= lsz) x = tr[x].ls;
        else if (k > lsz + 1) x = tr[x].rs, k -= lsz + 1;
        else return tr[x].val;
    }
}
int rank(int &rt, int v) {
    auto [l, r] = split(rt, v);
    int res = tr[l].sz;
    rt = merge(l, r);
    return res;
}
int pre(int &rt, int v) {
    auto [l, r] = split(rt, v);
    int x = l;
    while (tr[x].rs) x = tr[x].rs;
    int res = x ? tr[x].val : -1;
    rt = merge(l, r);
    return res;
}
int nxt(int &rt, int v) {
    auto [l, r] = split(rt, v - 1);
    int x = r;
    while (tr[x].ls) x = tr[x].ls;
    int res = x ? tr[x].val : -1;
    rt = merge(l, r);
    return res;
}

int main() {
    int n, q;
    n = read(), q = read();

    int rt = 0;
    for (int i = 0; i < n; ++i) {
        rt = merge(rt, new_node(read()));
    }

    while (q--) {
        int t, x;
        t = read(), x = read();

        if (t == 0) insert(rt, x);
        else if (t == 1) erase(rt, x);
        else if (t == 2) write(kth(rt, x)), putchar('\n');
        else if (t == 3) write(rank(rt, x)), putchar('\n');
        else if (t == 4) write(pre(rt, x)), putchar('\n');
        else if (t == 5) write(nxt(rt, x)), putchar('\n');
    }
}
