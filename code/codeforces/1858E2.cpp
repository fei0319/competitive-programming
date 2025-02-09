#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 1e6 + 19, MAXB = 20, T = 6;
const int MAXS = 2.1e7;

class PersistentSegment {
    struct Node {
        int ls, rs;
    };
    static int tot;
    static Node tr[MAXS];
    static void add(int node, int L, int R, int x) {
        if (L == R) {
            return;
        }
        int mid = (L + R) / 2;
        if (x <= mid) {
            add(tr[node].ls = copy(tr[node].ls), L, mid, x);
        } else {
            add(tr[node].rs = copy(tr[node].rs), mid + 1, R, x);
        }
    }
    static bool query(int node, int L, int R, int x) {
        if (!node) return false;
        if (L == R) return true;
        int mid = (L + R) / 2;
        if (x <= mid) return query(tr[node].ls, L, mid, x);
        else
            return query(tr[node].rs, mid + 1, R, x);
    }

public:
    static int L, R;
    static int copy(int node) {
        tr[++tot] = tr[node];
        return tot;
    }
    static void add(int node, int x) { add(node, L, R, x); }
    static bool query(int node, int x) { return query(node, L, R, x); }
};

int PersistentSegment::L = 1;
int PersistentSegment::R = 1e6;
int PersistentSegment::tot = 0;
PersistentSegment::Node PersistentSegment::tr[MAXS]{};

using ps = PersistentSegment;

struct Node {
    int f;
    int fa[MAXB - T];
    int rt;
    int ans;
    int prev;
} node[MAXN];

Node from(int x) {
    Node res;

    res.f = x;
    int f0 = x;
    for (int i = 1; i < (1 << T); ++i) {
        f0 = node[f0].f;
    }

    res.fa[0] = f0;
    for (int i = 1; i < MAXB - T; ++i) {
        res.fa[i] = node[res.fa[i - 1]].fa[i - 1];
    }
    res.rt = ps::copy(node[x].rt);
    res.ans = node[x].ans;

    return res;
}

int tot, now;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;

    while (q--) {
        std::string op;
        std::cin >> op;
        if (op == "+") {
            int x;
            std::cin >> x;
            tot += 1;
            node[tot] = from(now);
            node[tot].prev = now;
            now = tot;

            if (!ps::query(node[now].rt, x)) {
                ps::add(node[now].rt, x);
                node[now].ans += 1;
            }
        } else if (op == "-") {
            int k;
            std::cin >> k;

            int prev = now;
            for (int i = T; i < MAXB; ++i) {
                if (k & (1 << i)) {
                    now = node[now].fa[i - T];
                }
            }
            for (int i = 0; i < (k & ((1 << T) - 1)); ++i) {
                now = node[now].f;
            }

            node[++tot] = node[now];
            node[tot].prev = prev;
            now = tot;
        } else if (op == "!") {
            now = node[now].prev;
        } else {
            std::cout << node[now].ans << std::endl;
        }
    }

    return 0;
}