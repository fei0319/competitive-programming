#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 2e5 + 19, MOD = 998244353;

constexpr int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1)
            res = (ll)res * a % MOD;
        a = (ll)a * a % MOD, b >>= 1;
    }
    return res;
}

int fa[MAXN * 2];
int getf(int node) {
    return fa[node] == node ? node : fa[node] = getf(fa[node]);
}
void merge(int x, int y) {
    x = getf(x), y = getf(y);
    if (x > y) std::swap(x, y);
    fa[x] = y;
}

int n, m, a[MAXN];

int prev[MAXN];
int st[MAXN], top;
void build() {
    for (int i = 0; i < n; ++i) {
        if (prev[i] == -1) {
            continue;
        }
        while (top && st[top] >= prev[i]) {
            merge(st[top--], i);
        }
        st[++top] = i;
    }
}

bool check() {
    static bool t[MAXN];
    std::vector<int> x[2];
    for (int i = 0; i < n; ++i) {
        x[t[a[i]]].push_back(a[i]);
        t[a[i]] = !t[a[i]];
    }
    return x[0] == x[1];
}

int main(int argc, char *argv[]) {
    std::cin >> n;
    std::vector<int> vals;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        vals.push_back(a[i]);
    }

    std::sort(vals.begin(), vals.end());
    vals.resize(std::unique(vals.begin(), vals.end()) - vals.begin());
    for (int i = 0; i < n; ++i) {
        a[i] = std::lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
    }

    std::vector<std::vector<int>> pos(vals.size());
    for (int i = 0; i < n; ++i) {
        pos[a[i]].push_back(i);
    }

    if (!check()) {
        std::cout << qpow(2, vals.size() - 1) << '\n';
        return 0;
    }

    m = vals.size();
    std::iota(fa, fa + n + m, 0);
    std::fill(prev, prev + n, -1);
    for (int x = 0; x < m; ++x) {
        for (int i = 0; i + 1 < (int)pos[x].size(); i += 2) {
            prev[pos[x][i + 1]] = pos[x][i];
        }
    }
    build();
    for (int x = 0; x < m; ++x) {
        for (int i = 0; i + 1 < (int)pos[x].size(); i += 2) {
            merge(pos[x][i + 1], n + x);
        }
    }

    std::vector<int> indices;
    for (int i = n; i < n + m; ++i) {
        indices.push_back(getf(i));
    }
    std::sort(indices.begin(), indices.end());
    int cnt = std::unique(indices.begin(), indices.end()) - indices.begin();

    int ans = ll(qpow(2, vals.size()) - qpow(2, cnt)) * qpow(2, MOD - 2) % MOD;
    std::cout << (ans + MOD) % MOD << '\n';

    return 0;
}