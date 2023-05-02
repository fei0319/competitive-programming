#include <algorithm>
#include <cctype>
#include <cstdio>
#include <vector>

template <typename Tp> void read(Tp &res) {
    static char ch;
    ch = getchar(), res = 0;
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        res = res * 10 + ch - 48, ch = getchar();
}

constexpr int maxn = 1e6 + 19;

int n, k, a[maxn], now[maxn];
std::vector<int> pos[maxn];

struct SegmentTree {
    struct Node {
        int min, min_c, tag;
    } tr[maxn << 2];
    void build(int node, int L, int R) {
        if (L == R) {
            tr[node].min_c = 1;
            return;
        }
        int mid = (L + R) >> 1;
        build(node << 1, L, mid);
        build(node << 1 | 1, mid + 1, R);
        push_up(node);
    }
    void push_down(int node) {
        if (tr[node].tag == 0)
            return;
        int tag = tr[node].tag;
        tr[node << 1].min += tag;
        tr[node << 1].tag += tag;
        tr[node << 1 | 1].min += tag;
        tr[node << 1 | 1].tag += tag;
        tr[node].tag = 0;
    }
    void push_up(int node) {
        tr[node].min = std::min(tr[node << 1].min, tr[node << 1 | 1].min);
        tr[node].min_c = 0;
        if (tr[node << 1].min == tr[node].min)
            tr[node].min_c += tr[node << 1].min_c;
        if (tr[node << 1 | 1].min == tr[node].min)
            tr[node].min_c += tr[node << 1 | 1].min_c;
    }
    void modify(int node, int L, int R, int l, int r, const int &val) {
        if (l <= L && R <= r) {
            tr[node].min += val;
            tr[node].tag += val;
            return;
        }
        push_down(node);
        int mid = (L + R) >> 1;
        if (l <= mid)
            modify(node << 1, L, mid, l, r, val);
        if (r > mid)
            modify(node << 1 | 1, mid + 1, R, l, r, val);
        push_up(node);
    }
    int count(int node, int L, int R, int l, int r) {
        if (l <= L && R <= r) {
            if (tr[node].min == 0)
                return tr[node].min_c;
            else
                return 0;
        }
        push_down(node);
        int mid = (L + R) >> 1, res = 0;
        if (l <= mid)
            res += count(node << 1, L, mid, l, r);
        if (r > mid)
            res += count(node << 1 | 1, mid + 1, R, l, r);
        return res;
    }
} mt;

void cover(int x, int now, const int &val) {
    if (now + k < pos[x].size()) {
        int l = pos[x][now + k - 1], r = pos[x][now + k] - 1;
        mt.modify(1, 1, n, l, r, val);
        //    printf("%d %d %d\n", l, r, val);
    }
}

int main() {
    read(n), read(k);
    for (int i = 1; i <= n; ++i)
        read(a[i]), pos[a[i]].push_back(i);
    for (int i = 1; i <= int(1e6); ++i)
        pos[i].push_back(n + 1);

    mt.build(1, 1, n);

    for (int i = 1; i <= int(1e6); ++i) {
        cover(i, now[i], 1);
    }

    long long int ans = 0ll;
    for (int i = 1; i <= n; ++i) {
        ans += mt.count(1, 1, n, i, n);
        cover(a[i], now[a[i]], -1);
        cover(a[i], ++now[a[i]], 1);
    }

    printf("%lld\n", ans);
}