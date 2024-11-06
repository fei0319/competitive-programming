#include <bits/stdc++.h>

constexpr int maxn = 5e3 + 9;
using ll = long long int;

char s[maxn], t[maxn];

void solve(void) {
    int n, x, y;
    std::cin >> n >> x >> y;

    std::vector<int> pos;
    std::cin >> s + 1 >> t + 1;
    for (int i = 1; i <= n; ++i) {
        if (s[i] != t[i]) {
            pos.push_back(i);
        }
    }

    if (pos.size() % 2 == 1) {
        std::cout << -1 << std::endl;
        return;
    }

    if (x >= y) {
        if (pos.size() == 2ll && pos[0] == pos[1] - 1) {
            if ((pos[0] - 2 >= 1 || pos[1] + 2 <= n) && (ll)y * 2 <= x)
                std::cout << (ll)y * 2 << std::endl;
            else if ((pos[0] - 1 >= 1 && pos[1] + 1 <= n) &&
                     (ll)y * 3 <= x)
                std::cout << (ll)y * 3 << std::endl;
            else std::cout << x << std::endl;
        } else {
            std::cout << (ll)pos.size() / 2 * y << std::endl;
        }
        return;
    }
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