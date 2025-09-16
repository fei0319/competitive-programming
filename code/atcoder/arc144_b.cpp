// Problem: B - Gift Tax
// Contest: AtCoder - AtCoder Regular Contest 144
// URL: https://atcoder.jp/contests/arc144/tasks/arc144_b
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
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) res = res * 10 + ch - 48, ch = getchar();
}

const int maxn = 3e5 + 19;
int N, a, b, w[maxn];

bool check(int v) {
    ll need = 0;
    for (int i = 1; i <= N; ++i)
        if (w[i] > v) need += (w[i] - v) / b;
        else if (w[i] < v) need -= (v - w[i] + a - 1) / a;
    return need >= 0;
}

int main() {
    read(N), read(a), read(b);
    for (int i = 1; i <= N; ++i) read(w[i]);
    int l = 1, r = 1e9;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    printf("%d\n", l);
}

/*





















*/