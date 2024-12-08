#include <bits/stdc++.h>

using ll = long long int;
using ld = long double;

const int MAXN = 3e3 + 19;
const ld INF = 1e50L;

int n, m;
int q[MAXN], h, t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;

    std::vector<ld> f(m + 1, INF), g(m + 1);

    std::function<void(int, int, int, int)> solve = [&](int L, int R,
                                                        int l, int r) {
        if (l > r) return;
        if (L == R) {
            for (int i = l; i <= r; ++i) {
                g[i] = f[L] + (ld)i / (i - L);
            }
            return;
        }
        int mid = (l + r) / 2;

        int x = L;
        ld t = f[x] + (ld)mid / (mid - x);
        for (int i = L + 1; i < mid; ++i) {
            ld n_t = f[i] + (ld)mid / (mid - i);
            if (n_t < t) {
                x = i;
                t = n_t;
            }
        }
        g[mid] = t;
        solve(L, x, l, mid - 1);
        solve(x, R, mid + 1, r);
    };
    f[0] = 0;
    for (int i = 1; i <= n; ++i) {
        g[0] = INF;
        solve(0, m - 1, 1, m);
        f.swap(g);
    }

    std::cout << std::fixed << std::setprecision(12);
    std::cout << f[m] * 2 - n << '\n';

    return 0;
}