#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e5 + 19;

int n, a[maxn], b[maxn];

bool check(void) {
    if (n & 1)
        return false;
    std::sort(a + 1, a + 1 + n);
    int l = 1, r = n / 2 + 1;
    for (int i = 1; i <= n; ++i) {
        if (i & 1)
            b[i] = a[l++];
        else
            b[i] = a[r++];
    }
    b[0] = b[n];
    for (int i = 1; i <= n; ++i)
        if (b[i] == b[i - 1])
            return false;
    return true;
}

void solve(void) {
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];
    if (check()) {
        std::cout << "YES\n";
        for (int i = 1; i <= n; ++i)
            std::cout << b[i] << ' ';
        std::cout << '\n';
    } else
        std::cout << "NO\n";
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