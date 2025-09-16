#include <bits/stdc++.h>

constexpr int MAXS = 1.1e6 + 19;

struct Node {
    int cnt, sz;
    int v;
    void init(int val) {
        cnt = sz = 1;
        v = val;
    }
} tr[MAXS];
#define ls son[x][0]
#define rs son[x][1]
int fa[MAXS], son[MAXS][2];
void push_up(int x) { tr[x].sz = tr[ls].sz + tr[x].cnt + tr[rs].sz; }
void push_down(int x) {}
int get(int x) { return son[fa[x]][1] == x; }
bool isroot(int x) { return !fa[x]; }
void rotate(int x) {
    int f = fa[x], ff = fa[f], t = get(x);
    if (!isroot(f)) son[ff][get(f)] = x;
    son[f][t] = son[x][t ^ 1], fa[son[x][t ^ 1]] = f, push_up(f);
    son[x][t ^ 1] = f, fa[f] = x, fa[x] = ff, push_up(x);
}
void update(int x) {
    if (!isroot(x)) update(fa[x]);
    push_down(x);
}
void splay(int x) {
    update(x), push_up(x);
    for (; !isroot(x); rotate(x))
        if (!isroot(fa[x])) rotate(get(x) == get(fa[x]) ? fa[x] : x);
}

int tot;
void insert(int &rt, int v) {
    if (!rt) return rt = ++tot, tr[tot].init(v);
    int x = rt, p = 0;
    while (x && tr[x].v != v) p = x, x = son[x][v > tr[x].v];
    if (x) {
        tr[x].cnt += 1;
        splay(x), rt = x;
    } else {
        assert(p);
        son[p][v > tr[p].v] = ++tot, fa[tot] = p, tr[tot].init(v);
        splay(tot), rt = tot;
    }
}
int merge(int x, int y) {
    if (!x || !y) return x + y;
    while (rs) x = rs;
    splay(x);
    rs = y, fa[y] = x, push_up(x);
    return x;
}
void erase(int &rt, int v) {
    int x = rt;
    while (x && tr[x].v != v) x = son[x][v > tr[x].v];
    tr[x].cnt -= 1;
    splay(x), rt = x;
    if (tr[x].cnt == 0) {
        fa[ls] = fa[rs] = 0;
        rt = merge(ls, rs);
    }
}
int rank(int &rt, int v) {
    int x = rt, p = 0;
    int res = 1;
    while (x) {
        if (tr[x].v < v) res += tr[ls].sz + tr[x].cnt, p = x, x = rs;
        else p = x, x = ls;
    }
    splay(p), rt = p;
    return res;
}
int kth(int &rt, int k) {
    int x = rt;
    assert(k <= tr[x].sz);
    while (true) {
        if (k <= tr[ls].sz) x = ls;
        else if (k > tr[ls].sz + tr[x].cnt)
            k -= tr[ls].sz + tr[x].cnt, x = rs;
        else break;
    }
    splay(x), rt = x;
    return tr[x].v;
}
int prev(int &rt, int v) {
    int x = rt, p = 0, target = 0;
    while (x) {
        if (tr[x].v < v) {
            if (tr[x].cnt) target = x;
            p = x, x = rs;
        } else p = x, x = ls;
    }
    splay(p), rt = p;
    return tr[target].v;
}
int next(int &rt, int v) {
    int x = rt, p = 0, target = 0;
    while (x) {
        if (tr[x].v > v) {
            if (tr[x].cnt) target = x;
            p = x, x = ls;
        } else p = x, x = rs;
    }
    splay(p), rt = p;
    return tr[target].v;
}

void inspect() {
    for (int i = 1; i <= tot; ++i) {
        std::cout << tr[i].v << '(' << fa[i] << ',' << get(i) << ") ";
    }
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    int rt = 0;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        insert(rt, a);
    }

    int last = 0, ans = 0;
    while (m--) {
        int op, x;
        std::cin >> op >> x;
        x ^= last;
        if (op == 1) {
            insert(rt, x);
        } else if (op == 2) {
            erase(rt, x);
        } else if (op == 3) {
            last = rank(rt, x);
            ans ^= last;
        } else if (op == 4) {
            last = kth(rt, x);
            ans ^= last;
        } else if (op == 5) {
            last = prev(rt, x);
            ans ^= last;
        } else if (op == 6) {
            last = next(rt, x);
            ans ^= last;
        }
        // inspect();
    }

    std::cout << ans << '\n';
}
