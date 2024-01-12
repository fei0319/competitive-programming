#include <bits/stdc++.h>

template <typename Tp>
void chkmax(Tp &a, const Tp &b) {
    if (a < b)
        a = b;
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

const int maxn = 3e5 + 19;

int n, p[maxn], ans;
char s[maxn];

struct Tree {
    int tr[maxn];
    int query(int x) {
        int res = -1e9;
        for (; x; x -= x & -x)
            chkmax(res, tr[x]);
        return res;
    }
    void update(int x, int k) {
        for (; x <= n; x += x & -x)
            chkmax(tr[x], k);
    }
} m1, m2;

int main() {
    read(n);
    for (int i = 1; i <= n; ++i)
        read(p[i]), m1.tr[i] = m2.tr[i] = -1e9;
    std::scanf("%s", s + 1);
    for (int i = 1; i <= n; ++i) {
        int res = 0;
        chkmax(res, std::max(m1.query(p[i]), m2.query(n - p[i] + 1)) + 1);
        if (s[res + 1] == 'U')
            m1.update(p[i], res);
        else
            m2.update(n - p[i] + 1, res);
        chkmax(ans, res);
    }
    printf("%d\n", ans);
}