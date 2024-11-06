#include <algorithm>
#include <cstdio>
#include <vector>

constexpr int MAXN = 2e5 + 19, L = 20;
std::vector<int> G[MAXN];

struct Node {
    int mx, mn;
    int lmx, lmn, rmx, rmn;
    int tot;
    Node() {}
    Node(int _mx, int _mn, int _lmx, int _lmn, int _rmx, int _rmn,
         int _tot)
        : mx(_mx), mn(_mn), lmx(_lmx), rmx(_rmx), lmn(_lmn), rmn(_rmn),
          tot(_tot) {}
    Node(int x) {
        int max = std::max(x, 0), min = std::min(x, 0);
        *this = Node(max, min, max, min, max, min, x);
    }
    Node reverse() const { return Node(mx, mn, rmx, rmn, lmx, lmn, tot); }
    Node operator+(const Node &b) const {
        Node res;
        res.lmx = std::max(lmx, tot + b.lmx);
        res.lmn = std::min(lmn, tot + b.lmn);

        res.rmx = std::max(b.rmx, rmx + b.tot);
        res.rmn = std::min(b.rmn, rmn + b.tot);

        res.tot = tot + b.tot;

        res.mx = std::max({mx, b.mx, rmx + b.lmx});
        res.mn = std::min({mn, b.mn, rmn + b.lmn});

        return res;
    }
    void print() { printf("%d %d\n", mn, mx); }
};

int n, q;
char opt[12];

int fa[MAXN][L], dep[MAXN];
Node dp[MAXN][L];

Node calc(int u, int v) {
    if (dep[u] < dep[v]) std::swap(u, v);
    Node from_u = Node(0), from_v = Node(0);
    for (int i = L - 1; i >= 0; --i)
        if (dep[fa[u][i]] >= dep[v]) {
            from_u = dp[u][i] + from_u;
            u = fa[u][i];
        }
    for (int i = L - 1; i >= 0; --i)
        if (fa[u][i] != fa[v][i]) {
            from_u = dp[u][i] + from_u;
            u = fa[u][i];
            from_v = dp[v][i] + from_v;
            v = fa[v][i];
        }
    if (u != v)
        from_u = dp[u][0] + from_u, from_v = dp[v][0] + from_v,
        u = fa[u][0];
    return from_u.reverse() + dp[u][0] + from_v;
}

void solve() {
    scanf("%d", &q);

    n = 1;
    dep[1] = 1;
    for (int i = 0; i < L; ++i) dp[n][i] = Node(1);

    while (q--) {
        scanf("%s", opt);
        if (opt[0] == '+') {
            int v, x;
            scanf("%d%d", &v, &x);
            ++n;
            fa[n][0] = v;
            for (int i = 1; i < L; ++i) fa[n][i] = fa[fa[n][i - 1]][i - 1];
            dp[n][0] = Node(x);
            for (int i = 1; i < L; ++i)
                dp[n][i] = dp[fa[n][i - 1]][i - 1] + dp[n][i - 1];
            dep[n] = dep[v] + 1;
        } else {
            int u, v, k;
            scanf("%d%d%d", &u, &v, &k);
            Node res = calc(u, v);
            // res.print();
            puts(res.mn <= k && k <= res.mx ? "YES" : "NO");
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) solve();
}