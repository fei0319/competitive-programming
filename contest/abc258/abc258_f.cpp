// Problem: F - Main Street
// Contest: AtCoder - AtCoder Beginner Contest 258
// URL: https://atcoder.jp/contests/abc258/tasks/abc258_f
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
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
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        res = res * 10 + ch - 48, ch = getchar();
}

ll delta(const ll &a, const ll &b) {
    if (a > b)
        return a - b;
    return b - a;
}

int b, k, sx, sy, gx, gy;

ll __query(int sx, int sy, int gx, int gy) {
    return delta(sx, gx) + delta(sy, gy);
}

ll flr(ll x) {
    return x / b * b;
}
ll cel(ll x) {
    return flr(x + b - 1);
}

ll query(int sx, int sy, int gx, int gy) {
    if (sx / b != gx / b && sy / b != gy / b)
        return __query(sx, sy, gx, gy);
    if (sx / b != gx / b)
        std::swap(sx, sy), std::swap(gx, gy);
    if (sy == gy)
        return delta(sx, gx);
    return std::min({delta(sx, flr(sx)) + delta(gx, flr(gx)) +
                         __query(flr(sx), sy, flr(gx), gy),
                     delta(sx, flr(sx)) + delta(gx, cel(gx)) +
                         __query(flr(sx), sy, cel(gx), gy),
                     delta(sx, cel(sx)) + delta(gx, flr(gx)) +
                         __query(cel(sx), sy, flr(gx), gy),
                     delta(sx, cel(sx)) + delta(gx, cel(gx)) +
                         __query(cel(sx), sy, cel(gx), gy)});
}

void solve(void) {
    read(b), read(k), read(sx), read(sy), read(gx), read(gy);
    std::vector<std::pair<int, int>> s, g;

    s.emplace_back((sx + b - 1) / b * b, sy);
    g.emplace_back((gx + b - 1) / b * b, gy);

    s.emplace_back(sx / b * b, sy);
    g.emplace_back(gx / b * b, gy);

    s.emplace_back(sx, (sy + b - 1) / b * b);
    g.emplace_back(gx, (gy + b - 1) / b * b);

    s.emplace_back(sx, sy / b * b);
    g.emplace_back(gx, gy / b * b);

    ll ans = __query(sx, sy, gx, gy) * k;

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            ll res = 0;
            if (sx != s[i].first)
                res += delta(sx, s[i].first);
            if (gx != g[j].first)
                res += delta(gx, g[j].first);

            if (sy != s[i].second)
                res += delta(sy, s[i].second);
            if (gy != g[j].second)
                res += delta(gy, g[j].second);

            chkmin(ans, res * k + query(s[i].first, s[i].second, g[j].first,
                                        g[j].second));
        }

    printf("%lld\n", ans);
}

int main() {
    int t;
    read(t);
    while (t--)
        solve();
}

/*





















*/