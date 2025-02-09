// Problem: G - Reversible Cards 2
// Contest: AtCoder - UNICORN Programming Contest 2022(AtCoder Beginner
// Contest 269) URL: https://atcoder.jp/contests/abc269/tasks/abc269_g
// Memory Limit: 1024 MB Time Limit: 3000 ms
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
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) res = res * 10 + ch - 48, ch = getchar();
}

struct Node {
    int x, y;
    bool operator*(const Node &b) const {
        return (ll)x * b.y - (ll)b.x * y > 0;
    }
};

std::vector<Node> merge(const std::vector<Node> &a,
                        const std::vector<Node> &b) {
    int x = 0, y = 0;
    std::vector<Node> res;
    while (x < a.size() && y < b.size()) {
        if (a[x] * b[y]) res.push_back(a[x++]);
        else
            res.push_back(b[y++]);
    }
    while (x < a.size()) res.push_back(a[x++]);
    while (y < b.size()) res.push_back(b[y++]);
    return res;
}

const int maxn = 2e5 + 19, inf = 1e9;

int n, m, a[maxn], b[maxn], ans[maxn];
std::vector<Node> v[maxn];
std::vector<Node> solve(int l, int r) {
    if (l == r) return v[l];
    int mid = (l + r) >> 1;
    return merge(solve(l, mid), solve(mid + 1, r));
}

int main() {
    read(n), read(m);
    for (int i = 1; i <= n; ++i) {
        read(a[i]), read(b[i]);
        if (a[i] < b[i]) {
            v[i].push_back((Node){a[i], 0 - inf});
            v[i].push_back((Node){b[i] - a[i], 1 - 0});
            v[i].push_back((Node){-b[i], inf - 1});
        } else {
            v[i].push_back((Node){b[i], 1 - inf});
            v[i].push_back((Node){a[i] - b[i], 0 - 1});
            v[i].push_back((Node){-a[i], inf});
        }
    }
    for (int i = 0; i <= m; ++i) ans[i] = inf;
    auto res = solve(1, n);
    ll x = 0, y = 0;
    for (auto t : res) {
        x += t.x, y += t.y;
        if (y + (ll)inf * n < ans[x]) ans[x] = y + (ll)inf * n;
    }

    for (int i = 0; i <= m; ++i) printf("%d\n", ans[i]);
}