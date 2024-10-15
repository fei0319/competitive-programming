#include <bits/stdc++.h>

using i64 = int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> p(n);
    for (auto &[x, y] : p) {
        std::cin >> x >> y;
    }

    i64 ans = 0;
    for (auto [x, y] : p) {
        ans += x - y;
    }
    ans = std::max(ans, -ans);

    i64 res = 0;
    std::vector<int> arr;
    for (auto [x, y] : p) {
        res += x + y;
        arr.push_back(-2 * std::min(x, y));
        arr.push_back(-2 * std::max(x, y));
    }

    std::sort(arr.begin(), arr.end());
    std::array<i64, 3> sum{};
    for (int i = arr.size() - 1; i >= arr.size() - n; --i) {
        sum[0] += arr[i];
    }
    sum[1] = sum[0] - arr[arr.size() - n];
    sum[2] = sum[1] - arr[arr.size() - n + 1];

    for (auto [x, y] : p) {
        int u = -2 * std::max(x, y), v = -2 * std::min(x, y);
        int p_u = std::upper_bound(arr.begin(), arr.end(), u) - arr.begin() - 1;
        int p_v = std::upper_bound(arr.begin(), arr.end(), v) - arr.begin() - 1;
        if (p_u < arr.size() - n) {
            if (p_v < arr.size() - n + 1) {
                ans = std::max(ans, res + sum[2] + u + v);
            } else {
                ans = std::max(ans, res + sum[1] + u);
            }
        } else {
            ans = std::max(ans, res + sum[0]);
        }
    }

    std::cout << ans << '\n';
}
