#include <bits/stdc++.h>

using ll = long long int;

const int MAXN = 3e3 + 19;

int n, k, p, s[MAXN];

void solve() {
    std::cin >> n >> k >> p;

    // f: #[x+y=i]
    // g: #[y=i]

    std::vector<int> f(k + 1), g(k + 1);
    f[0] = 1;
    g[0] = 1;

    for (int i = 1; i <= n; ++i) {
        std::vector<int> n_f(k + 1), n_g(k + 1);

        n_f[0] = g[0];
        for (int j = 1; j <= k; ++j) {
            n_f[j] = (n_f[j - 1] + g[j]) % p;
        }

        s[0] = f[0];
        for (int j = 1; j <= k; ++j) {
            s[j] = (s[j - 1] + f[j]) % p;
        }

        for (int j = 0; j <= k; ++j) {
            n_g[0] = (n_g[0] + (ll)f[j] * (j + 1)) % p;
            n_g[0] = (n_g[0] - (ll)g[j] * j) % p;
        }
        for (int j = 1; j <= k; ++j) {
            n_g[j] = s[k - j];
        }

        f.swap(n_f), g.swap(n_g);
    }

    std::cout << (g[0] + p) % p << '\n';
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