// Problem: D. Mark and Lightbulbs
// Contest: Codeforces - Codeforces Round #807 (Div. 2)
// URL: https://codeforces.com/contest/1705/problem/D
// Memory Limit: 256 MB
// Time Limit: 1500 ms
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

const int maxn = 2e5 + 19;
int n;
bool ta, tb;
std::vector<int> a, b;

int myAbs(int a) { return a > 0 ? a : -a; }

void rda(auto &a, bool &t) {
    static char s[maxn];
    scanf("%s", s + 1);
    t = (s[1] == '1');
    a.clear();
    int l = 1, r = 1;
    while (l <= n) {
        while (r < n && s[r + 1] == s[r])
            ++r;
        a.push_back(l);
        l = r + 1, r = l;
    }
}

void solve() {
    read(n);
    rda(a, ta), rda(b, tb);
    if (ta != tb || a.size() != b.size()) {
        puts("-1");
        return;
    }
    int len = a.size();
    ll ans = 0;
    for (int i = 0; i < len; ++i)
        ans += myAbs(a[i] - b[i]);
    printf("%lld\n", ans);
}

int main() {
    int T;
    read(T);
    while (T--)
        solve();
}

/*





















*/