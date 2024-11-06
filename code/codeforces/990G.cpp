#pragma GCC optimize(2)
#include <bits/stdc++.h>

template <typename Tp>
void read(Tp &res) {
    static char ch;
    ch = getchar(), res = 0;
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) res = res * 10 + ch - 48, ch = getchar();
}

typedef long long int ll;
const int maxn = 2e5 + 19;

struct Node {
    int num, val;
} edge[maxn * 64];
int cnt;
int rub[maxn * 20], rub_t;
std::vector<int> con[maxn];
inline void add(int node, int num, ll val) {
    int x = rub_t ? rub[rub_t--] : ++cnt;
    edge[x].num = num, edge[x].val = val;
    con[node].push_back(x);
}

std::vector<int> G[maxn];
int n, a[maxn], pre[maxn];

int dv[maxn], pwr[maxn], tot;
void Dfs(int node, int t, int v) {
    if (t == tot) {
        add(node, v, 1);
        return;
    }
    ++t;
    Dfs(node, t, v);
    for (int i = 1; i <= pwr[t]; ++i) {
        v *= dv[t];
        Dfs(node, t, v);
    }
}
std::vector<int> tag[maxn];
std::vector<int> dvs;
void decom(int node, int a) {
    if (a == 166320 && !dvs.empty()) {
        for (int i : dvs) add(node, i, 1);
        return;
    }
    while (!tag[a].empty() && con[tag[a].back()].empty())
        tag[a].pop_back();
    if (tag[a].empty()) {
        int x = a;
        tot = 0;
        for (int i = 2; i * i <= x; ++i)
            if (x % i == 0) {
                dv[++tot] = i, pwr[tot] = 0;
                while (x % i == 0) x /= i, ++pwr[tot];
            }
        if (x > 1) dv[++tot] = x, pwr[tot] = 1;
        Dfs(node, 0, 1);
        std::sort(con[node].begin(), con[node].end(),
                  [](int x, int y) { return edge[x].num < edge[y].num; });
    } else {
        for (int i : con[tag[a].back()]) add(node, edge[i].num, 1);
    }
    tag[a].push_back(node);
    if (a == 166320) {
        for (int i : con[node]) dvs.push_back(edge[i].num);
    }
}

ll ans[maxn];

void dfs(int node, int f) {
    for (int to : G[node]) {
        if (to == f) continue;
        dfs(to, node);
        if (con[node].empty()) {
            decom(node, a[node]);
            for (int i : con[node]) ans[edge[i].num] += edge[i].val;
        }
        int ptr = 0;
        for (int i : con[to])
            if (a[node] % edge[i].num == 0) {
                while (edge[con[node][ptr]].num < edge[i].num) ++ptr;
                int x = con[node][ptr];
                ans[edge[i].num] += (ll)edge[i].val * edge[x].val;
                edge[x].val += edge[i].val;
                if (rub_t < maxn * 10 - 1) rub[++rub_t] = i;
            }
        std::vector<int> em;
        em.swap(con[to]);
    }
    if (con[node].empty()) {
        decom(node, a[node]);
        for (int i : con[node]) ans[edge[i].num] += edge[i].val;
    }
}

int main() {
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 2, x, y; i <= n; ++i) {
        read(x), read(y);
        G[x].push_back(y), G[y].push_back(x);
    }
    dfs(1, 0);
    const int N = 2e5;
    for (int i = N; i >= 1; --i)
        for (int j = i + i; j <= N; j += i) ans[i] -= ans[j];
    for (int i = 1; i <= N; ++i)
        if (ans[i]) printf("%d %lld\n", i, ans[i]);
}