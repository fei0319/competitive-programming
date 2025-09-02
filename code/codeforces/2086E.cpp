#include <bits/stdc++.h>

using i64 = int64_t;
using u64 = uint64_t;

constexpr i64 base(int b) { return ((i64{1} << ((b + 1) * 2)) - 1) / 3; }

template <>
struct std::hash<std::pair<i64, i64>> {
    u64 operator()(const std::pair<i64, i64> &p) const {
        const u64 x = p.first;
        const u64 y = p.second;
        return (x ^ (y * y)) + x + y;
    }
};

auto dfs(i64 x, i64 k) -> i64 {
    static std::unordered_map<std::pair<i64, i64>, i64> mem{};
    if (const auto it = mem.find({x, k}); it != mem.end()) {
        return it->second;
    }
    i64 &res = mem[{x, k}];

    if (k == 0) return res = 1;
    if (x == 0) return res = 0;

    const int b = *std::ranges::lower_bound(
        std::views::iota(0, 31) | std::views::reverse, true, {},
        [&](int b) { return base(b) <= x; });
    const i64 v = base(b);

    return res = dfs(x - v, k - 1) + dfs(v - 1, k);
}

void solve() {
    i64 l, r, k;
    std::cin >> l >> r >> k;
    std::cout << dfs(r, k) - dfs(l - 1, k) << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) solve();
}
