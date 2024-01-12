#include <algorithm>
#include <iostream>
#include <vector>

using ll = long long int;

std::vector<std::pair<std::string, ll>> ans;

constexpr int MAXN = 1e2 + 19;
constexpr ll inf = 1e18;

int n, m;
std::vector<std::pair<int, int>> G[MAXN];
ll a[MAXN];
bool vist[MAXN];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v, y;
        std::cin >> u >> v >> y;
        G[u].emplace_back(v, y);
        G[v].emplace_back(u, y);
    }

    for (int i = 1; i <= n; ++i)
        a[i] = inf;
    a[n] = 0;

    while (true) {
        static int q[MAXN], head, tail;
        head = 1, tail = 0;
        for (int i = 1; i <= n; ++i)
            if (a[i] == 0 && !vist[i]) {
                vist[i] = true;
                q[++tail] = i;
            }
        while (head <= tail) {
            int node = q[head++];
            for (auto [to, y] : G[node]) {
                a[to] = std::min(a[to], (ll)y);
                if (a[to] == 0 && !vist[to]) {
                    vist[to] = true;
                    q[++tail] = to;
                }
            }
        }

        if (a[1] == 0)
            break;
        ll t = inf;
        std::string s(n, '0');
        for (int i = 1; i <= n; ++i) {
            if (a[i]) {
                t = std::min(t, a[i]);
                s[i - 1] = '1';
            }
        }
        for (int i = 1; i <= n; ++i)
            if (a[i])
                a[i] -= t;
        ans.emplace_back(s, t);
    }

    ll T = 0;
    for (auto [s, t] : ans)
        T += t;
    if (T >= ll(1e18)) {
        std::cout << "inf\n";
        return 0;
    }
    std::cout << T << ' ' << ans.size() << '\n';
    for (auto [s, t] : ans)
        std::cout << s << ' ' << t << '\n';
}