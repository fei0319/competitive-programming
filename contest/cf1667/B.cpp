// Problem: B. Optimal Partition
// Contest: Codeforces Round #783 (Div. 1)
// URL: https://codeforces.com/contest/1667/problem/B
// Memory Limit: 256 MB
// Time Limit: 4000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
typedef long long int ll;
template <typename Tp> void chkmax(Tp &a, const Tp &b) { a = std::max(a, b); }
template <typename Tp> void chkmin(Tp &a, const Tp &b) { a = std::min(a, b); }
template <typename Tp> void read(Tp &res) {
    static char ch;
    ch = getchar(), res = 0;
    bool flag = false;
    while (!isdigit(ch))
        flag |= (ch == '-'), ch = getchar();
    while (isdigit(ch))
        res = res * 10 + ch - 48, ch = getchar();
    if (flag)
        res = -res;
}

const int maxn = 5e5 + 19, inf = 1e9;

int n, x[maxn], dp[maxn];
ll s[maxn];
std::vector<ll> t;

struct Tree {
    int tr[maxn];
    void clear(void) {
        for (int i = 1; i <= n + 1; ++i)
            tr[i] = -inf;
    }
    void update(int x, int k) {
        for (; x <= n + 1; x += x & -x)
            chkmax(tr[x], k);
    }
    int query(int x) {
        int res = -inf;
        for (; x; x -= x & -x)
            chkmax(res, tr[x]);
        return res;
    }
} m1, m2, m3;

int main() {
    int T;
    read(T);
    while (T--) {
        read(n);
        t.clear(), t.push_back(0ll);
        for (int i = 1; i <= n; ++i)
            read(s[i]), s[i] += s[i - 1], t.push_back(s[i]);
        std::sort(t.begin(), t.end()),
            t.resize(std::unique(t.begin(), t.end()) - t.begin());
        for (int i = 0; i <= n; ++i)
            x[i] = std::lower_bound(t.begin(), t.end(), s[i]) - t.begin() + 1;
        m1.clear(), m2.clear(), m3.clear();
        m1.update(x[0], 0), m2.update(x[0], 0), m3.update(x[0], 0);
        for (int i = 1; i <= n; ++i) {
            dp[i] = std::max(
                {m1.query(x[i] - 1) + i, m2.query(x[i]), m3.query(n + 1) - i});
            m1.update(x[i], dp[i] - i);
            m2.update(x[i], dp[i]);
            m3.update(x[i], dp[i] + i);
        }
        //	for(int i = 1; i < n; ++i) printf("%d ", dp[i]);
        printf("%d\n", dp[n]);
    }
}