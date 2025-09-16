// Problem: D - Bridges
// Contest: AtCoder - AtCoder Regular Contest 143
// URL: https://atcoder.jp/contests/arc143/tasks/arc143_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <map>
#include <set>
#include <string>
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

const int maxn = 2e5 + 19;

int n, x, y, a[maxn];

int main() {
    read(n), read(x), read(y);
    for (int i = 1; i <= n; ++i) read(a[i]), a[i] %= (x + y);
    if (x <= y) {
        int cnt = 0;
        for (int i = 1; i <= n; ++i)
            if (a[i] >= x) ++cnt;
        puts(cnt ? "First" : "Second");
    } else {
        int gx = 0, lx = 0;
        for (int i = 1; i <= n; ++i)
            if (a[i] >= x) ++gx;
            else if (a[i] >= y) ++lx;
        puts(gx && !lx ? "First" : "Second");
    }
}

/*





















*/