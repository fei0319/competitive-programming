#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n), b(m);

    for (int &i : a) {
        std::cin >> i;
    }
    for (int &i : b) {
        std::cin >> i;
    }

    auto abs = [](int x) { return x > 0 ? x : -x; };
    auto ans = 0ll;
    for (int i = 1; i < n; ++i) {
        ans += abs(a[i] - a[i - 1]);
    }
    for (int i = 1; i < m; ++i) {
        ans += abs(b[i] - b[i - 1]);
    }
    std::cout << ans << '\n';
}
