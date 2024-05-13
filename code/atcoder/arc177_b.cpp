#include <bits/stdc++.h>

int main() {
    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    std::vector<uint8_t> ans;
    std::vector<std::pair<int, int>> a;
    for (int l = 0, r; l < n; l = r + 1) {
        r = l;
        if (s[l] == '1') {
            while (r + 1 < n && s[r + 1] == '1') {
                ++r;
            }
            a.emplace_back(l, r);
        }
    }

    std::reverse(a.begin(), a.end());
    for (auto [l, r] : a) {
        for (int i = 0; i < r + 1; ++i) {
            ans.push_back(true);
        }
        for (int i = 0; i < l; ++i) {
            ans.push_back(false);
        }
    }

    std::cout << ans.size() << '\n';
    for (auto i : ans) {
        std::cout << (i ? 'A' : 'B');
    }
}