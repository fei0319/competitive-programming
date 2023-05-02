// Problem: B. I love AAAB
// Contest: Codeforces - Codeforces Global Round 20
// URL: https://codeforces.com/contest/1672/problem/B
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

const int maxn = 2e5 + 19;
char s[maxn];
int n;

int main() {
    int T;
    read(T);
    while (T--) {
        std::scanf("%s", s + 1), n = std::strlen(s + 1);
        int len = 0, ans = (s[n] == 'B');
        for (int i = 1; i <= n; ++i) {
            if (s[i] == 'A')
                ++len;
            if (s[i] == 'B') {
                if (len == 0)
                    ans = 0;
                --len;
            }
        }
        puts(ans ? "YES" : "NO");
    }
}