// Problem: E. Count Seconds
// Contest: Codeforces - CodeTON Round 2 (Div. 1 + Div. 2, Rated, Prizes!)
// URL: https://codeforces.com/contest/1704/problem/E
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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

typedef __int128 ll;

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

const int maxn = 1e3 + 19, mod = 998244353;

int n, m, v[maxn];
ll a[maxn];
std::vector<int> G[maxn];

bool empty() {
    for (int i = 1; i <= n; ++i)
        if (a[i]) return false;
    return true;
}

void solve() {
    read(n), read(m);
    for (int i = 1; i <= n; ++i) {
        int tmp;
        read(tmp), a[i] = tmp;
        G[i].clear();
    }
    for (int i = 1; i <= m; ++i) {
        int u, v;
        read(u), read(v);
        G[u].push_back(v);
    }
    int ans = 0;
    while (!empty()) {
        for (int i = 1; i <= n; ++i) v[i] = a[i] ? -1 : 0;
        for (int i = 1; i <= n; ++i)
            if (a[i]) {
                for (int to : G[i]) ++v[to];
            }
        ll t = 0;
        bool off = false;
        for (int i = 1; i <= n; ++i) {
            if (v[i] == -1 && (a[i] < a[t] || v[t] != -1)) t = i;
            if (v[i] && !a[i]) {
                off = true;
                break;
            }
        }
        t = a[t];
        if (off) t = 1;
        for (int i = 1; i <= n; ++i) a[i] += t * v[i];
        ans = (ans + t) % mod;
    }
    printf("%d\n", ans);
}

int main() {
    int T;
    read(T);
    while (T--) solve();
}

/*





















*/