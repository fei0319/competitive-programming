// Problem: B. Rain
// Contest: Codeforces - Codeforces Round #810 (Div. 1)
// URL: https://codeforces.com/contest/1710/problem/B
// Memory Limit: 256 MB
// Time Limit: 4000 ms
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

const int maxn = 1e6 + 19;

int n, m;
int x[maxn], p[maxn];
int pos[maxn], cnt;
ll a[maxn];

std::vector<std::pair<int, int>> rain[maxn];
std::vector<ll> Gx[maxn], Gy[maxn], Lx[maxn];
std::multiset<ll> G, L;

void add_limit(std::vector<ll> *Tx, int i, const ll &x) { Tx[i].push_back(x); }

ll les[maxn], grt[maxn];
ll cl[maxn], cg[maxn];
int getpos(int x) { return std::lower_bound(pos + 1, pos + 1 + cnt, x) - pos; }

void add(ll *v, ll *cnt, int i, const ll &x) { v[i] += x, ++cnt[i]; }

void del(ll *v, ll *cnt, int i, const ll &x) { v[i] += x, --cnt[i]; }

ll getmax(const std::multiset<ll> &s) { return *--s.end(); }

bool ans[maxn];

int main() {
    int T;
    read(T);
    while (T--) {
        read(n), read(m), cnt = 0;
        for (int i = 1; i <= n; ++i) {
            read(x[i]), read(p[i]), ans[i] = true;
            pos[++cnt] = x[i] - p[i];
            pos[++cnt] = x[i];
            pos[++cnt] = x[i] + 1;
            pos[++cnt] = x[i] + p[i];
        }
        std::sort(pos + 1, pos + 1 + cnt);
        cnt = std::unique(pos + 1, pos + 1 + cnt) - pos - 1;
        G.clear(), L.clear();
        for (int i = 1; i <= cnt; ++i) {
            rain[i].clear();
            grt[i] = cg[i] = 0;
            les[i] = cl[i] = 0;
            Gx[i].clear(), Gy[i].clear(), Lx[i].clear();
        }
        for (int i = 1; i <= n; ++i) {
            rain[getpos(x[i])].emplace_back(p[i], i);
            add(grt, cg, getpos(x[i] - p[i]), p[i] - x[i]);
            del(grt, cg, getpos(x[i] + 1), -(p[i] - x[i]));
            add(les, cl, getpos(x[i] + 1), p[i] + x[i]);
            del(les, cl, getpos(x[i] + p[i]), -(p[i] + x[i]));
        }
        for (int i = 1; i <= cnt; ++i) {
            grt[i] += grt[i - 1], cg[i] += cg[i - 1];
            les[i] += les[i - 1], cl[i] += cl[i - 1];
            a[i] = pos[i] * (cg[i] - cl[i]) + grt[i] + les[i];
            if (a[i] > m) {
                a[i] -= m;
                add_limit(Gx, 1, a[i] + pos[i]);
                add_limit(Gy, getpos(pos[i] + 1), a[i] + pos[i]);
                add_limit(Lx, getpos(pos[i] + 1), a[i] - pos[i]);
            }
        }
        for (int i = 1; i <= cnt; ++i) {
            for (auto j : Gx[i])
                G.insert(j);
            for (auto j : Gy[i])
                G.erase(G.find(j));
            for (auto j : Lx[i])
                L.insert(j);
            ll req = 0;
            if (!G.empty())
                chkmax(req, getmax(G) - pos[i]);
            if (!L.empty())
                chkmax(req, getmax(L) + pos[i]);
            std::sort(rain[i].begin(), rain[i].end());
            for (int j = 0; j < (int)rain[i].size(); ++j) {
                if (rain[i][j].first >= req)
                    break;
                ans[rain[i][j].second] = false;
            }
        }
        for (int i = 1; i <= n; ++i)
            putchar(ans[i] ? '1' : '0');
        puts("");
    }
}

/*





















*/