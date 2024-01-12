// Problem: P4182 [USACO18JAN]Lifeguards P
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4182
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
template <typename Tp>
void read(Tp &res) {
    static char ch;
    ch = getchar(), res = 0;
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        res = res * 10 + ch - 48, ch = getchar();
}

const int maxn = 1e5 + 9, maxk = 109;

int n, k, dp[maxk][maxn];
std::deque<int> q[maxn];
int maxv[maxn];

struct Node {
    int l, r;
} node[maxn], tmp[maxn];
int cnt;

inline int f(int m, int k) {
    return dp[k + 1 - m][k] - node[k].r;
}

struct Tree {
    int tr[maxn];
    void update(int x, int k) {
        for (; x <= n + 1; x += x & -x)
            tr[x] += k;
    }
    int query(int x) {
        int res = 0;
        for (; x; x -= x & -x)
            res += tr[x];
        return res;
    }
} mt;

std::vector<int> arr;

int main() {
    read(n), read(k);
    for (int i = 1; i <= n; ++i)
        read(node[i].l), read(node[i].r), arr.push_back(node[i].l);
    node[n + 1].l = 1e9 + 3, node[n + 1].r = node[n + 1].l,
             arr.push_back(node[n + 1].l);
    ++n;
    std::sort(node + 1, node + 1 + n,
              [](const Node &a, const Node &b) { return a.r > b.r; });
    std::sort(arr.begin(), arr.end());
    arr.resize(std::unique(arr.begin(), arr.end()) - arr.begin());
    for (int i = 1; i <= n; ++i) {
        int x = std::lower_bound(arr.begin(), arr.end(), node[i].l) -
                arr.begin() + 1;
        if (mt.query(x) == 0)
            tmp[++cnt] = node[i];
        mt.update(x, 1);
    }
    k -= n - cnt, n = cnt;
    for (int i = 1; i <= n; ++i)
        node[i] = tmp[i];
    std::sort(node + 1, node + 1 + n,
              [](const Node &a, const Node &b) { return a.r < b.r; });
    for (int i = 0; i <= k; ++i)
        maxv[i] = -1e9;
    maxv[1] = 0;
    int now = 0;
    for (int i = 1; i <= n; ++i) {
        if (i > k)
            q[i - k - 1].clear();
        for (int j = i; j >= std::max(i - k, 0); --j)
            while (!q[j].empty() && node[q[j].front()].r <= node[i].l)
                q[j].pop_front();
        while (now + 1 <= n && node[now + 1].r <= node[i].l) {
            ++now;
            for (int j = 0; j <= std::min(now - 1, k); ++j)
                chkmax(maxv[now - j + 1], dp[j][now]);
        }
        for (int j = 0; j <= std::min(i - 1, k); ++j) {
            dp[j][i] = maxv[i - j] + node[i].r - node[i].l;
            if (j == i - 1)
                chkmax(dp[j][i], node[i].r - node[i].l);
            if (!q[i - j].empty())
                chkmax(dp[j][i], f(i - j, q[i - j].front()) + node[i].r);
            //			printf("dp[%d][%d] = %d\n", i, j, dp[j][i]);
        }
        for (int j = 0; j <= std::min(i - 1, k); ++j) {
            int x = dp[j][i] - node[i].r;
            while (!q[i - j + 1].empty() &&
                   f(i - j + 1, q[i - j + 1].back()) <= x)
                q[i - j + 1].pop_back();
            q[i - j + 1].push_back(i);
        }
    }
    printf("%d\n", dp[k][n]);
}