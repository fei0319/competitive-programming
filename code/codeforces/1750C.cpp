#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 2e5 + 19;

int n;
char a[maxn], b[maxn];

void solve(void) {
    std::cin >> n;
    std::cin >> a + 1;
    std::cin >> b + 1;
    int cnt[] = {0, 0};
    for (int i = 1; i <= n; ++i) ++cnt[a[i] == b[i]];
    if (cnt[0] != n && cnt[1] != n) {
        std::cout << "NO\n";
        return;
    }
    std::cout << "YES\n";
    std::vector<std::pair<int, int>> ans;
    if (cnt[0] == n) {
        ans.emplace_back(1, n);
        for (int i = 1; i <= n; ++i) a[i] = (a[i] == '1' ? '0' : '1');
    }
    std::vector<int> one;
    for (int i = 1; i <= n; ++i)
        if (a[i] == '1') one.push_back(i);
    while (!one.empty()) {
        int x, y;
        if ((int)one.size() >= 2) {
            x = one.back();
            one.pop_back();
            y = one.back();
            one.pop_back();
            if (x > y) std::swap(x, y);
            ans.emplace_back(x, y - 1);
            ans.emplace_back(x + 1, y);
        } else {
            x = one.back();
            one.pop_back();
            if (x != 1) {
                ans.emplace_back(1, x);
                ans.emplace_back(1, x - 1);
            } else {
                ans.emplace_back(x, n);
                ans.emplace_back(x + 1, n);
            }
        }
    }
    std::cout << ans.size() << std::endl;
    for (auto [x, y] : ans) std::cout << x << ' ' << y << '\n';
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