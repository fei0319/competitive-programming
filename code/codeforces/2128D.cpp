#include <bits/stdc++.h>

using i64 = int64_t;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> p(n);
    std::for_each(p.begin(), p.end(), [](auto &x) { std::cin >> x; });

    i64 ans{};
    i64 pre{};
    int cnt{};
    for (int l = 0, r; l < n; l = r + 1) {
        r = l + 1 < n && p[l + 1] > p[l] ? l + 1 : l;
        if (l == r) {
            ans += pre + cnt + 1;
            pre += cnt + 1;
            cnt += 1;
        } else {
            ans += (pre + cnt) * 2 + 3;
            pre += cnt + 2;
            cnt += 2;
        }
    }

    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
}
