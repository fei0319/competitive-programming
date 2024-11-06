#include <bits/stdc++.h>

using ll = long long int;

void solve(void) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    int const INF = 1e9;
    int x = INF, y = INF;
    int ans = 0;

    for (int i : a) {
        if (x > y) std::swap(x, y);

        if (i <= x) x = i;
        else if (i <= y) y = i;
        else x = i, ans += 1;
    }

    std::cout << ans << '\n';
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}