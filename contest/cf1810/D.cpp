#include <bits/stdc++.h>

using ll = long long int;

constexpr ll inf = 1e18;

ll mein_ceil(ll a, ll b) { return (a + b - 1) / b; }

void solve(void) {
    ll L = 1, R = inf;

    int T;
    std::cin >> T;

    while (T--) {
        int type, a, b, n;
        std::cin >> type >> a >> b;
        if (type == 1) {
            std::cin >> n;
            ll l = ll(a - b) * (n - 2) + a + 1, r = ll(a - b) * (n - 1) + a;
            if (n == 1) {
                l = 1, r = a;
            }
            if (r >= L && l <= R) {
                L = std::max(L, l);
                R = std::min(R, r);
                std::cout << "1 ";
            } else {
                std::cout << "0 ";
            }
        } else {
            if (R <= a) {
                std::cout << "1 ";
            } else {
                ll l = mein_ceil(L - a, a - b) + 1,
                   r = mein_ceil(R - a, a - b) + 1;
                if (l == r) {
                    std::cout << l << ' ';
                } else {
                    std::cout << "-1 ";
                }
            }
        }
    }
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