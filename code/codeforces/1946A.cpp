#include <bits/stdc++.h>

using ll = long long int;

void solve() {
    int n;
    std::vector<int> a;

    std::cin >> n;

    a.resize(n);
    for (int &i : a) {
        std::cin >> i;
    }

    std::sort(a.begin(), a.end());
    int p = (n + 1) / 2 - 1;
    int ans = 1;
    while (p + ans < n && a[p + ans] == a[p]) {
        ++ans;
    }
    std::cout << ans << '\n';
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