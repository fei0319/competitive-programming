// Problem: A - AB Palindrome
// Contest: AtCoder - AtCoder Regular Contest 145
// URL: https://atcoder.jp/contests/arc145/tasks/arc145_a
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

const int maxn = 2e5 + 19;

int N;
char s[maxn];

bool check(void) {
    int l = 1, r = N;
    bool pre = false;
    while (l < r) {
        if (s[l] != s[r]) {
            if (s[l] == 'A' || l == r - 1) {
                if (!pre) return false;
                pre = true;
            } else {
                pre = true;
            }
        } else
            pre = true;
        ++l, --r;
    }
    return true;
}

int main() {
    read(N);
    scanf("%s", s + 1);
    if (check()) puts("Yes");
    else
        puts("No");
}

/*





















*/