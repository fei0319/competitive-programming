// Problem: B - Prefix?
// Contest: AtCoder - UNIQUE VISION Programming Contest 2022 Summer (AtCoder
// Beginner Contest 268) URL: https://atcoder.jp/contests/abc268/tasks/abc268_b
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

std::string s, t;

int main() {
    std::cin >> s >> t;
    if (s.size() > t.size())
        return puts("No"), 0;
    for (int i = 0; i < (int)s.size(); ++i)
        if (s[i] != t[i])
            return puts("No"), 0;
    puts("Yes");
}