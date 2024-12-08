// Problem: P2742 [USACO5.1]圈奶牛Fencing the Cows /【模板】二维凸包
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2742
// Memory Limit: 128 MB
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
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) res = res * 10 + ch - 48, ch = getchar();
}

const int maxn = 1e5 + 19;

struct Node {
    long double x, y;
    Node(long double __x = 0, long double __y = 0) { x = __x, y = __y; }
    bool operator<(const Node &b) const {
        return x != b.x ? x < b.x : y < b.y;
    }
    Node operator+(const Node &b) const { return Node(x + b.x, y + b.y); }
    Node operator-(const Node &b) const { return Node(x - b.x, y - b.y); }
    bool operator*(const Node &b) const { return x * b.y - b.x * y > 0; }
} p[maxn];

int n, st[maxn], top;

int main() {
    read(n);
    for (int i = 1; i <= n; ++i) std::scanf("%Lf%Lf", &p[i].x, &p[i].y);
    std::sort(p + 1, p + 1 + n);
    std::stable_sort(p + 2, p + 1 + n, [](const Node &a, const Node &b) {
        return (a - p[1]) * (b - p[1]);
    });
    for (int i = 1; i <= n; ++i) {
        while (top >= 2 &&
               (p[i] - p[st[top - 1]]) * (p[st[top]] - p[st[top - 1]]))
            --top;
        st[++top] = i;
    }
    long double ans = 0;
    st[0] = st[top];
    for (int i = 1; i <= top; ++i) {
        auto dx = p[st[i]].x - p[st[i - 1]].x,
             dy = p[st[i]].y - p[st[i - 1]].y;
        ans += std::sqrt(dx * dx + dy * dy);
    }
    printf("%.2Lf\n", ans);
}