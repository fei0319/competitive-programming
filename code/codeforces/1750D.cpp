#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19, mod = 998244353;

int n, m, a[maxn];

void solve(void) {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    int ans = 1;
    for (int i = 2; i <= n; ++i) {
        if (a[i - 1] % a[i] != 0) {
            ans = 0;
            break;
        }
        int k = a[i - 1] / a[i], t = m / a[i];
        std::vector<int> p;
        for (int j = 2; j * j <= k; ++j)
            if (k % j == 0) {
                while (k % j == 0) k /= j;
                p.push_back(j);
            }
        if (k != 1) p.push_back(k);
        //	std::cout << "P:";
        //	for(int j : p) std::cout << j << ' ';
        //	std::cout << std::endl;
        int s = 1 << p.size();
        ll res = 0;
        for (int j = 0; j < s; ++j) {
            int v = 1, f = 1;
            for (int u = 0; u < (int)p.size(); ++u)
                if (j & (1 << u)) v *= p[u], f = -f;
            //		std::cout << v << ' ' << f << '\n';
            res += f * (t / v);
        }
        //	std::cout << "r" << res << std::endl;
        ans = (ll)ans * res % mod;
    }
    std::cout << ans << std::endl;
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