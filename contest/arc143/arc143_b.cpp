// Problem: B - Counting Grids
// Contest: AtCoder - AtCoder Regular Contest 143
// URL: https://atcoder.jp/contests/arc143/tasks/arc143_b
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

const int maxn = 500 + 19, mod = 998244353;

int N, fact[maxn * maxn], ifact[maxn * maxn];

int A(int n, int m) { return (ll)fact[n] * ifact[n - m] % mod; }

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1)
            res = (ll)res * a % mod;
        a = (ll)a * a % mod, b >>= 1;
    }
    return res;
}

int main() {
    read(N);
    fact[0] = 1;
    for (int i = 1; i <= N * N; ++i)
        fact[i] = (ll)fact[i - 1] * i % mod;
    ifact[N * N] = qpow(fact[N * N], mod - 2);
    for (int i = N * N - 1; i >= 0; --i)
        ifact[i] = (ll)ifact[i + 1] * (i + 1) % mod;
    int res = fact[N * N], c = (ll)N * N % mod * fact[(N - 1) * (N - 1)] % mod;
    for (int i = 1; i <= N * N; ++i) {
        if (i - 1 < N - 1 || N * N - i < N - 1)
            continue;
        res =
            (res - (ll)c * A(i - 1, N - 1) % mod * A(N * N - i, N - 1) % mod) %
            mod;
    }
    res = (res + mod) % mod;
    printf("%d\n", res);
}

/*
tot = (N*N)!




















*/