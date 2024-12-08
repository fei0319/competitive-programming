#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

int n, k, b[maxn], a[maxn];

std::vector<int> ring[maxn];
bool vist[maxn];

int qpow(int a, int b, const int &mod) {
    int res = 1;
    while (b) {
        if (b & 1) res = (ll)res * a % mod;
        a = (ll)a * a % mod, b >>= 1;
    }
    return res;
}

void construct(int m, int K) {
    if (K >= 20) return;
    int num = 1 << K, step = qpow(2, k, num * m);
    while (ring[m].size() >= num) {
        std::vector<int> now(num * m);
        for (int i = 0; i < num; ++i) {
            int x = ring[m].back();
            ring[m].pop_back();
            for (int j = 0; j < m; ++j) {
                now[(i + (ll)j * step) % now.size()] = x;
                x = b[x];
            }
        }
        for (int i = 0; i < now.size(); ++i)
            a[now[i]] = now[(i + 1) % now.size()];
    }
}

void solve(void) {
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        std::cin >> b[i];
    }

    for (int i = 1; i <= n; ++i) {
        a[i] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        vist[i] = 0;
        ring[i].clear();
    }
    for (int i = 1; i <= n; ++i)
        if (!vist[i]) {
            int now = i, len = 0;
            while (!vist[now]) {
                vist[now] = 1, ++len;
                now = b[now];
            }
            ring[len].push_back(now);
        }

    for (int m = 1; m <= n; ++m) {
        if (m % 2 == 1) {
            for (int i = std::min(k, 20); i >= 0; --i) {
                construct(m, i);
            }
        } else {
            construct(m, k);
        }
    }

    for (int i = 1; i <= n; ++i)
        if (!a[i]) {
            std::cout << "NO\n";
            return;
        }
    std::cout << "YES\n";
    for (int i = 1; i <= n; ++i) std::cout << a[i] << ' ';
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}