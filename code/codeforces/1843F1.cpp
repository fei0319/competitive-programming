#include <algorithm>
#include <cstdio>
#include <vector>

constexpr int MAXN = 2e5 + 19;
std::vector<int> G[MAXN];

int n, q;
int max[MAXN], min[MAXN], cmx[MAXN], cmn[MAXN];
char opt[12];

void solve() {
    scanf("%d", &q);
    n = 1;
    max[n] = 1, min[n] = 0;
    cmx[n] = 1, cmn[n] = 0;
    while (q--) {
        scanf("%s", opt);
        if (opt[0] == '+') {
            int v, x;
            scanf("%d%d", &v, &x);
            ++n;
            cmx[n] = std::max(0, x + cmx[v]);
            cmn[n] = std::min(0, x + cmn[v]);
            max[n] = std::max(cmx[n], max[v]);
            min[n] = std::min(cmn[n], min[v]);
        } else {
            int u, v, k;
            scanf("%d%d%d", &u, &v, &k);
            puts(min[v] <= k && k <= max[v] ? "YES" : "NO");
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) solve();
}