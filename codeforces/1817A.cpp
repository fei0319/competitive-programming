#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

int n, q, a[maxn], l[maxn], r[maxn], belong[maxn], len[maxn], tot, s[maxn];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }

    for (int i = 1; i <= n; ++i) {
        if (a[i] > a[i - 1]) {
            belong[i] = ++tot;
            l[belong[i]] = i;
            r[belong[i]] = i;
        } else {
            belong[i] = tot;
            r[belong[i]] = i;
        }
        ++len[belong[i]];
    }

    for (int i = 1; i <= tot; ++i) {
        s[i] = s[i - 1] + std::min(len[i], 2);
    }

    while (q--) {
        int L, R;
        std::cin >> L >> R;
        if (belong[L] == belong[R]) {
            std::cout << std::min(R - L + 1, 2) << '\n';
        } else {
            int ans = std::min(r[belong[L]] - L + 1, 2) +
                      std::min(R - l[belong[R]] + 1, 2);
            ans += s[belong[R] - 1] - s[belong[L]];
            std::cout << ans << '\n';
        }
    }

    return 0;
}