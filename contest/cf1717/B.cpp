// Problem: B. Madoka and Underground Competitions
// Contest: Codeforces - Codeforces Round #818 (Div. 2)
// URL: https://codeforces.com/contest/1717/problem/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
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

const int maxn = 5e2 + 19;

int n, k, r, c;
bool is[maxn][maxn];

int main() {
    int T;
    read(T);
    while (T--) {
        read(n), read(k), read(r), read(c);
        int m = n / k;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                is[i][j] = false;
        is[(r - 1) % k + 1][(c - 1) % k + 1] = true;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < m; ++j)
                if ((r - 1) / k == i && (c - 1) / k == j) {
                    std::set<int> s;
                    for (int x = 1; x <= k; ++x)
                        if (x != (c - 1) % k + 1)
                            s.insert(x);
                    for (int x = 1; x <= k; ++x)
                        if (x != (r - 1) % k + 1) {
                            auto it = s.begin();
                            is[x][*it] = true;
                            s.erase(it);
                        }
                }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j)
                putchar(is[(i - 1) % k + 1][(j - 1) % k + 1] ? 'X' : '.');
            puts("");
        }
    }
}