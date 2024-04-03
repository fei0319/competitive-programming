#include <algorithm>
#include <iostream>
#include <vector>

constexpr int N = 3;

int a[19], l;

int main() {
    std::cin >> a[2] >> a[3] >> a[4] >> l;

    std::vector<std::pair<int, std::pair<int, int>>> ans;

    std::vector<int> v(N, 0);
    for (int i = 1; i <= l; ++i) {
        std::for_each(v.begin(), v.end(), [](int &x) { x += 1; });
        std::vector<std::pair<int, int>> p;
        if (a[4]) {
            p = {{4, 1}, {3, 2}, {2, 1}, {3, 1}};
        } else {
            p = {{3, 1}, {2, 1}};
        }
        for (auto [j, nl] : p) {
            int x = -1, num = 0;
            for (int k = 0; k < N; ++k) {
                if (v[k] >= j) {
                    num += 1;
                }
                if (v[k] >= j && (x == -1 || v[k] < v[x])) {
                    x = k;
                }
            }
            if (a[j] && num >= nl && x != -1) {
                --a[j];
                v[x] = 0;
                ans.emplace_back(x + 1, std::make_pair(i - j, i));
                break;
            }
        }
    }

    std::cout << ans.size() << '\n';
    for (auto p : ans) {
        std::cout << p.first << ' ' << p.second.first << ' ' << p.second.second
                  << '\n';
    }
}