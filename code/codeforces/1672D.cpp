// Problem: D. Cyclic Rotation
// Contest: Codeforces - Codeforces Global Round 20
// URL: https://codeforces.com/contest/1672/problem/D
// Memory Limit: 256 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
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

const int maxn = 2e5 + 19;
int n, cnt[maxn], a[maxn], b[maxn];

int main() {
    int T;
    read(T);
    while (T--) {
        read(n);
        for (int i = 1; i <= n; ++i) cnt[i] = 0;
        for (int i = 1; i <= n; ++i) read(a[i]);
        for (int i = 1; i <= n; ++i) read(b[i]);
        int ptr = n;
        bool ans = true;
        for (int i = n; i >= 1; --i) {
            if (ptr == 0 || a[i] != b[ptr]) {
                if (cnt[a[i]]) {
                    --cnt[a[i]];
                    continue;
                }
                ans = false;
                break;
            }
            --ptr;
            while (ptr >= 1 && a[i] == b[ptr]) --ptr, ++cnt[a[i]];
        }
        puts(ans ? "YES" : "NO");
    }
}