#include <bits/stdc++.h>

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
        std::cin.get(ch);
    }
}

template <typename T>
void write(const T &res) {
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
        tr[1].clear();
    }
    void insert(const LL &a, const int &b) {
        int node = 1;
        tr[node].sum += b;
        tr[node].min = std::min(tr[node].min, a);

        for (int i = B; i >= 0; --i) {
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

    LL dfs(int node, int m, LL D, LL min) {}

    LL solve(int m) {
        return dfs(1, m, 0, 0);
    }
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

    for (int i = 1; i <= n; ++i) {
        S::insert(a[i], b[i]);
    }

    write(S::solve(m));
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