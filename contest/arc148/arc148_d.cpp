// Problem: D - mod M Game
// Contest: AtCoder - AtCoder Regular Contest 148
// URL: https://atcoder.jp/contests/arc148/tasks/arc148_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
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
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        res = res * 10 + ch - 48, ch = getchar();
}

int n, m;
std::set<int> s;

int rep(int x) {
    return (x + m / 2) % m;
}

int main() {
    read(n), read(m);
    int cnt = 0;
    for (int i = 1; i <= n + n; ++i) {
        int x;
        read(x);
        if (s.find(x) != s.end())
            s.erase(x);
        else if (m % 2 == 0 && s.find(rep(x)) != s.end())
            s.erase(rep(x)), ++cnt;
        else
            s.insert(x);
    }
    if (!s.empty())
        return puts("Alice"), 0;
    puts(cnt & 1 ? "Alice" : "Bob");
}