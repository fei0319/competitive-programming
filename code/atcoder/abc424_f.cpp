#include <bits/stdc++.h>

using u64 = uint64_t;
std::mt19937_64 rng(std::random_device{}());

void solve() {
    int n, q;
    std::cin >> n >> q;

    std::vector<u64> tr(n + 1);
    auto update = [&](int x, u64 k) {
        for (; x <= n; x += x & -x) tr[x] ^= k;
    };
    auto query = [&](int x) {
        u64 res = 0;
        for (; x; x -= x & -x) res ^= tr[x];
        return res;
    };

    while (q--) {
        int a, b;
        std::cin >> a >> b;

        if (a > b) {
            std::swap(a, b);
        }

        if (query(a) != query(b)) {
            std::cout << "No\n";
            continue;
        }

        std::cout << "Yes\n";
        const u64 h = rng();
        update(a, h);
        update(b, h);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();
}
