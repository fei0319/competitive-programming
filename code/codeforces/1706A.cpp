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
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        res = res * 10 + ch - 48, ch = getchar();
}

const int maxn = 1e5 + 19;
int n, a, m;
char s[maxn];

int main() {
    int T;
    read(T);
    while (T--) {
        read(n), read(m);
        for (int i = 1; i <= m; ++i)
            s[i] = 'B';
        for (int i = 1; i <= n; ++i) {
            read(a);
            if (m + 1 - a < a && s[m + 1 - a] == 'B')
                a = m + 1 - a;
            if (s[a] == 'A')
                a = m + 1 - a;
            s[a] = 'A';
        }
        for (int i = 1; i <= m; ++i)
            putchar(s[i]);
        puts("");
    }
}

/*





















*/