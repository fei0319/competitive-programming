#include <bits/stdc++.h>

using i64 = int64_t;
namespace ranges = std::ranges;

void solve() {
    int n, k;
    std::cin >> n >> k;
    i64 x;
    std::cin >> x;

    std::vector<int> a(n);
    for (int &i : a) std::cin >> i;

    std::vector<i64> s(n);
    std::inclusive_scan(a.rbegin(), a.rend(), s.begin(), std::plus<>{},
                        i64{});

    const i64 sum = s.back();
    const i64 pre = (x - 1) / sum * sum;
    const i64 rest = x - pre;

    const int r = ranges::lower_bound(s, rest) - s.begin();

    const i64 ans =
        static_cast<i64>(n) * k - static_cast<i64>(pre / sum) * n - r;
    std::cout << std::max(ans, i64{}) << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) solve();
}
