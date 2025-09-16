// Problem: E - Packing Potatoes
// Contest: AtCoder - AtCoder Beginner Contest 258
// URL: https://atcoder.jp/contests/abc258/tasks/abc258_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>
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

const int maxn = 4e5 + 19;

int n, q, x, w[maxn], nxt[maxn][70];
ll s[maxn];

ll sum(int l, int r) {
    if (l == 0) return s[r];
    else return s[r] - s[l - 1];
}

int query(ll k) {
    int now = 0;
    for (int i = 60; i >= 0; --i)
        if (k >= (1ll << i)) {
            k -= (1ll << i);
            now = nxt[now][i];
        }
    return now;
}

int main() {
    read(n), read(q), read(x);
    for (int i = 0; i < n; ++i) read(w[i]);
    s[0] = w[0];
    for (int i = 1; i < n * 2; ++i) s[i] = s[i - 1] + w[i % n];
    for (int i = 0; i < n; ++i) {
        ll rest = x % s[n - 1];
        int l = 0, r = n * 2 - 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (sum(i, mid) < rest) l = mid + 1;
            else r = mid;
        }
        nxt[i][0] = (l + 1) % n;
    }
    for (int i = 1; i < 70; ++i)
        for (int j = 0; j < n; ++j) nxt[j][i] = nxt[nxt[j][i - 1]][i - 1];
    while (q--) {
        ll k;
        read(k);
        int now = query(k - 1);
        //	printf("%d\n", now);
        ll ans = ll(x / s[n - 1]) * n, rest = x % s[n - 1];
        int l = 0, r = n * 2 - 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (sum(now, mid) < rest) l = mid + 1;
            else r = mid;
        }
        ans += l - now + 1;
        printf("%lld\n", ans);
    }
}

/*





















*/