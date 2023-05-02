// Problem: B. Making Towers
// Contest: Codeforces - Codeforces Round #809 (Div. 2)
// URL: https://codeforces.com/contest/1706/problem/B
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

const int maxn = 1e5 + 19;
std::vector<int> pos[maxn];
int n, c[maxn];

int main() {
    int T;
    read(T);
    while (T--) {
        read(n);
        for (int i = 1; i <= n; ++i) {
            read(c[i]);
            pos[i].clear();
        }
        for (int i = 1; i <= n; ++i)
            pos[c[i]].push_back(i);
        for (int i = 1; i <= n; ++i) {
            int sz = pos[i].size(), ans = 0, cur[] = {0, 0};
            for (int j = 0; j < sz; ++j) {
                chkmax(cur[pos[i][j] & 1], 1);
                chkmax(cur[pos[i][j] & 1], cur[pos[i][j] & 1 ^ 1] + 1);
                chkmax(ans, cur[pos[i][j] & 1]);
            }
            printf("%d ", ans);
        }
        puts("");
    }
}

/*





















*/