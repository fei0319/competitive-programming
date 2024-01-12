// Problem: B - dp
// Contest: AtCoder - AtCoder Regular Contest 148
// URL: https://atcoder.jp/contests/arc148/tasks/arc148_b
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
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

const int maxn = 5e3 + 19;

int n;
char s[maxn];
char ans[maxn], tmp[maxn];

bool cmp(void) {
    for (int i = 1; i <= n; ++i)
        if (ans[i] != tmp[i])
            return tmp[i] < ans[i];
    return false;
}

void rev(int l, int r, char *t) {
    for (int i = 1; i < l; ++i)
        t[i] = s[i];
    for (int i = r + 1; i <= n; ++i)
        t[i] = s[i];
    for (int i = l; i <= r; ++i)
        t[i] = (s[r + l - i] == 'd' ? 'p' : 'd');
}

int main() {
    read(n);
    std::scanf("%s", s + 1);
    int p = 0;
    for (int i = 1; i <= n; ++i)
        if (s[i] == 'p') {
            p = i;
            break;
        }
    if (p == 0) {
        for (int i = 1; i <= n; ++i)
            putchar(s[i]);
        return 0;
    }
    rev(p, p, ans);
    for (int i = p + 1; i <= n; ++i) {
        rev(p, i, tmp);
        if (cmp())
            for (int j = 1; j <= n; ++j)
                ans[j] = tmp[j];
    }
    for (int i = 1; i <= n; ++i)
        putchar(ans[i]);
}