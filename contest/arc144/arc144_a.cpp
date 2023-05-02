// Problem: A - Digit Sum of 2x
// Contest: AtCoder - AtCoder Regular Contest 144
// URL: https://atcoder.jp/contests/arc144/tasks/arc144_a
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

template <typename Tp> void chkmax(Tp &a, const Tp &b) { a = std::max(a, b); }
template <typename Tp> void chkmin(Tp &a, const Tp &b) { a = std::min(a, b); }

template <typename Tp> void read(Tp &res) {
    static char ch;
    ch = getchar(), res = 0;
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        res = res * 10 + ch - 48, ch = getchar();
}

int main() {
    int N;
    read(N);
    printf("%d\n", N + N);
    if (N % 4)
        printf("%d", N % 4), N -= N % 4;
    for (int i = 1; i <= N / 4; ++i)
        putchar('4');
}

/*





















*/