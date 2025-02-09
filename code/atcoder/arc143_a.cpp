// Problem: A - Three Integers
// Contest: AtCoder - AtCoder Regular Contest 143
// URL: https://atcoder.jp/contests/arc143/tasks/arc143_a
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

int main() {
    ll a[3];
    read(a[0]), read(a[1]), read(a[2]);
    std::sort(a, a + 3);
    //(a - x) + (b - x) = (c - x)
    ll x = a[0] + a[1] - a[2];
    if (x < 0ll) puts("-1");
    else
        printf("%lld\n", a[2]);
}

/*





















*/