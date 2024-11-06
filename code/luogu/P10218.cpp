#include <algorithm>
#include <cstdint>
#include <format>
#include <iostream>
#include <numeric>

using LL = __int128;
using ll = int64_t;

constexpr int B = 120;
constexpr int MAXN = 1e5 + 19;
constexpr int MAXS = 1.2e7 + 19;
constexpr LL INF = LL(1) << 125;

template <typename T>
void read(T &res) {
    res = 0;
    char ch;
    std::cin.get(ch);
    while (!isdigit(ch)) {
        std::cin.get(ch);
    }
    while (isdigit(ch)) {
        res = res * 10 + (ch - 48);
        if (std::cin.eof()) break;
        std::cin.get(ch);
    }
}

template <typename T>
void write(const T &res) {
    if (res < 0) {
        std::cout << '-';
        return write(-res);
    }
    if (res >= 10) {
        write(res / 10);
    }
    std::cout << char(res % 10 + 48);
}

namespace S {
    struct Node {
        ll sum;
        LL min;
        int son[2];
        void clear() {
            sum = 0;
            min = INF;
            son[0] = son[1] = 0;
        }
    } tr[MAXS];
    int tot;
    void clear() {
        tot = 1;
        tr[0].clear();
        tr[1].clear();
    }
    void insert(const LL &a, const int &b, int hb) {
        int node = 1;
        tr[node].sum += b;
        tr[node].min = std::min(tr[node].min, a);

        for (int i = hb; i >= 0; --i) {
            int to = bool(a & (LL(1) << i));
            if (!tr[node].son[to]) {
                tr[node].son[to] = ++tot;
                tr[tot].clear();
            }
            node = tr[node].son[to];
            tr[node].sum += b;
            tr[node].min = std::min(tr[node].min, a);
        }
    }

    LL dfs(int node, const int &m, const int &b, const LL &ans,
           const LL &X, const LL &min) {

        if (b == -1) {
            return ans;
        }
        if (!node) {
            return std::min(min + X, ans) + (LL(1) << (b + 1)) - 1;
        }

        bool ok = false;
        LL res = -INF;

        // ans = 1
        for (int x : {0, 1}) {
            ll n_m = m - tr[tr[node].son[x]].sum;
            LL n_ans = ans + (LL(1) << b);
            LL n_X = X + (LL(x) << b);
            LL n_min = std::min(min, tr[tr[node].son[x]].min);
            if (n_m >= 0 && n_min + n_X + (LL(1) << b) - 1 >= n_ans) {
                ok = true;
                res = std::max(res, dfs(tr[node].son[!x], n_m, b - 1,
                                        n_ans, n_X, n_min));
            }
        }

        if (ok) {
            return res;
        }

        // ans = 0
        for (int x : {0, 1}) {
            ll n_m = m;
            LL n_X = X + (LL(x) << b);
            LL n_min = min;
            if (n_min + n_X + (LL(1) << b) - 1 >= ans) {
                res = std::max(res, dfs(tr[node].son[x], n_m, b - 1, ans,
                                        n_X, n_min));
            }
        }

        return res;
    }

    LL solve(int m, int hb) { return dfs(1, m, hb, 0, 0, INF); }
} // namespace S

int n, m, k;
LL a[MAXN];
int b[MAXN];

void solve() {
    S::clear();

    read(n), read(m), read(k);

    for (int i = 1; i <= n; ++i) {
        read(a[i]);
    }
    for (int i = 1; i <= n; ++i) {
        read(b[i]);
    }

    if (std::accumulate(b + 1, b + 1 + n, 0LL) <= m) {
        write(*std::min_element(a + 1, a + 1 + n) + (LL(1) << k) - 1);
        std::cout << std::endl;
        return;
    }

    for (int i = 1; i <= n; ++i) {
        S::insert(a[i], b[i], k - 1);
    }

    write(S::solve(m, k - 1));
    std::cout << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int c, T;
    read(c), read(T);
    while (T--) {
        solve();
    }
}