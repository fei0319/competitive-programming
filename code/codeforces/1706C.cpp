// Problem: C. Qpwoeirut And The City
// Contest: Codeforces - Codeforces Round #809 (Div. 2)
// URL: https://codeforces.com/contest/1706/problem/C
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

const int maxn = 1e5 + 19;
int h[maxn], n;

ll solve(int b) {
    ll res = 0ll;
    for (int i = b; i < n; i += 2) {
        if (h[i] <= std::max(h[i - 1], h[i + 1]))
            res += std::max(h[i - 1], h[i + 1]) - h[i] + 1;
    }
    return res;
}

ll dp[maxn][2];
int cal(int i) {
    if (h[i] > std::max(h[i - 1], h[i + 1])) return 0;
    return std::max(h[i - 1], h[i + 1]) - h[i] + 1;
}
ll dyp(void) {
    for (int i = 1; i <= n; ++i) dp[i][0] = dp[i][1] = 1e18;
    dp[2][0] = cal(2), dp[3][1] = cal(3);
    for (int i = 4; i < n; ++i) {
        dp[i][0] = dp[i - 2][0] + cal(i);
        dp[i][1] = std::min(dp[i - 2][1], dp[i - 3][0]) + cal(i);
    }
    //	for(int i = 1; i <= n; ++i) printf("dp%d={%lld,%lld}\n", i,
    // dp[i][0],
    // dp[i][1]);
    return std::min(dp[n - 2][0], std::min(dp[n - 1][0], dp[n - 1][1]));
}

int main() {
    int T;
    read(T);
    while (T--) {
        read(n);
        for (int i = 1; i <= n; ++i) read(h[i]);
        ll ans = solve(2);
        if (n % 2 == 0) chkmin(ans, dyp());
        printf("%lld\n", ans);
    }
}

/*





















*/