#include <algorithm>
#include <cstdio>
#include <vector>
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
    ll lmax, rmax, max, sum;
};

Node merge(const Node &l, const Node &r) {
    return (Node){
        std::max(l.lmax, l.sum + r.lmax), std::max(r.rmax, r.sum + l.rmax),
        std::max({l.max, r.max, l.rmax + r.lmax}), l.sum + r.sum};
}

int n, a[1 << 18], q;

std::vector<Node> dfs(int L, int R) {
    if (L == R) {
        return std::vector<Node>{(Node){std::max(a[L], 0),
                                        std::max(a[L], 0),
                                        std::max(a[L], 0), a[L]}};
    }
    int mid = (L + R) >> 1, len = (R - L + 1) >> 1;
    std::vector<Node> lv(dfs(L, mid)), rv(dfs(mid + 1, R)), res(len << 1);
    for (int i = 0; i < len; ++i) {
        res[i] = merge(lv[i], rv[i]);
        res[i + len] = merge(rv[i], lv[i]);
    }
    return res;
}

int main() {
    read(n);
    for (int i = 0; i < (1 << n); ++i) std::scanf("%d", a + i);
    auto res = dfs(0, (1 << n) - 1);
    int now = 0;
    read(q);
    while (q--) {
        int k;
        read(k);
        now ^= 1 << k;
        printf("%lld\n", res[now].max);
    }
}