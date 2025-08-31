#include <bits/stdc++.h>

using i64 = int64_t;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> p(n);
    for (int &i : p) {
        std::cin >> i;
    }

    std::deque<int> dq(p.begin(), p.end());
    std::vector<int> arr{};

    std::string ans{};
    for (int _ = 0; _ < n; ++_) {
        if (dq.empty()) {
            break;
        }
        if (dq.size() == 1) {
            ans += 'L';
            break;
        }

        auto check = [](int x, int y, int z) {
            return !(x < y && y < z) && !(x > y && y > z);
        };
        if (arr.empty() || check(arr.back(), dq.front(), dq.back())) {
            arr.push_back(dq.back());
            ans += "LR";
        } else {
            arr.push_back(dq.front());
            ans += "RL";
        }
        dq.pop_front();
        dq.pop_back();
    }

    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
}
