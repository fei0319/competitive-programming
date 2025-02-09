// Problem: C. Virus
// Contest: Codeforces - CodeTON Round 2 (Div. 1 + Div. 2, Rated, Prizes!)
// URL: https://codeforces.com/contest/1704/problem/C
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

const int maxn = 1e6 + 19;
int n, m, a[maxn];
std::vector<int> all;

int main() {
    int T;
    read(T);
    while (T--) {
        read(n), read(m);
        for (int i = 1; i <= m; ++i) read(a[i]);
        std::sort(a + 1, a + 1 + m), a[0] = a[m] - n;
        all.clear();
        for (int i = 1; i <= m; ++i)
            if (a[i] - a[i - 1] - 1 > 0)
                all.push_back(a[i] - a[i - 1] - 1);
        std::sort(all.begin(), all.end());
        int ans = 0;
        for (int i = 0; i <= m * 2; i += 2) {
            if (all.empty()) break;
            int v = all.back() - i * 2;
            all.pop_back();
            if (v == 1) ++ans;
            else if (v > 1)
                ans += v - 1;
        }
        printf("%d\n", n - ans);
    }
}

/*





















*/