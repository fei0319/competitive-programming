#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>

using ll = long long int;
using ld = long double;
const int MAXN = 1e6 + 19;

int n, m;
ll a[MAXN], b[MAXN];
ll ans;

const std::function<bool(int, int)> comp = [](int x, int y) {
    return a[x] * y < a[y] * x;
};

std::vector<int> c;
void solve(ll x, int p) {
    for (int i : c) {
        ll v = std::min({a[i], x, (ll)i * p});
        a[i] -= v;
        x -= v;
        ans += v;

        if (x == 0) {
            break;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        c.push_back(i);
    }
    for (int i = 1; i <= m; ++i) {
        std::cin >> b[i];
    }

    std::sort(c.rbegin(), c.rend(), comp);
    for (int i = 1; i <= m; ++i) {
        solve(b[i], i);
    }
    std::cout << ans << '\n';
}