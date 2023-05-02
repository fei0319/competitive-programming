#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e6 + 19;

int n, x, a[maxn];

void solve(void) {
    std::cin >> n >> x;
    if (n % x != 0) {
        std::cout << "-1\n";
        return;
    }
    std::cout << x << ' ';
    for (int i = 2; i < n; ++i)
        a[i] = i;
    int now = x, ptr = x + x;
    for (; ptr < n; ptr += now) {
        if (n % ptr == 0) {
            a[now] = ptr;
            now = ptr;
        }
    }
    a[now] = n;
    for (int i = 2; i < n; ++i)
        std::cout << a[i] << ' ';
    std::cout << 1 << '\n';
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