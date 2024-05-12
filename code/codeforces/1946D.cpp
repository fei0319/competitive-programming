#include <bits/stdc++.h>

using ll = long long int;

constexpr int B = 29;

int solve(std::vector<int> a, std::vector<int> b) {
    auto check = [&](int x) {
        for (int i : b) {
            if (x & (1 << i)) {
                return false;
            }
        }
        return true;
    };

    int res = 0, now = 0;
    for (int i = 0; i < a.size(); ++i) {
        now ^= a[i];
        if (check(now)) {
            now = 0;
            res += 1;
        } else if (i == a.size() - 1) {
            return 0;
        }
    }
    return res;
}

void solve() {
    int n, x;
    std::cin >> n >> x;

    std::vector<int> a(n);
    for (int &i : a) {
        std::cin >> i;
    }

    int xor_sum = 0;
    for (int i : a) {
        xor_sum ^= i;
    }
    if (xor_sum > x) {
        std::cout << "-1\n";
        return;
    }

    int ans = 1;
    for (int i = B; i >= -1; --i) {
        if (i != -1 && !(x & (1 << i))) {
            continue;
        }

        std::vector<int> b;
        for (int j = B; j > i; --j) {
            if (!(x & (1 << j))) {
                b.push_back(j);
            }
        }
        if (i != -1) {
            b.push_back(i);
        }

        ans = std::max(ans, solve(a, b));
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