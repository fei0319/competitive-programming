#include <bits/stdc++.h>

using ll = long long int;

void solve(void) {
    int w, d, h;
    std::cin >> w >> d >> h;
    int a, b, f, g;
    std::cin >> a >> b >> f >> g;
    int u = std::min(g + abs(f - a) + b, f + abs(g - b) + a);
    a = w - a, b = d - b;
    f = w - f, g = d - g;
    int v = std::min(g + abs(f - a) + b, f + abs(g - b) + a);
    std::cout << h + std::min(u, v) << '\n';
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