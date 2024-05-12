// Problem: B - AB Game
// Contest: AtCoder - AtCoder Regular Contest 145
// URL: https://atcoder.jp/contests/arc145/tasks/arc145_b
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <iostream>
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
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        res = res * 10 + ch - 48, ch = getchar();
}

ll n, a, b;

int main() {
    read(n), read(a), read(b);
    if (a > n) {
        puts("0");
        return 0;
    }
    if (a <= b) {
        printf("%lld\n", n - a + 1);
        return 0;
    }
    printf("%lld\n", b * (n / a - 1) + std::min(n % a + 1, b));
}

/*





















*/