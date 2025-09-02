#include <bits/stdc++.h>

using i64 = int64_t;
namespace ranges = std::ranges;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> p(n);
    for (int &i : p) {
        std::cin >> i;
        --i;
    }

    std::vector<int> d(n);
    for (int &i : d) {
        std::cin >> i;
        --i;
    }

    std::unordered_set<int> s;
    for (int d : d) {
        for (int x = d; !s.contains(x); x = p[x]) {
            s.insert(x);
        }
        std::cout << s.size() << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) solve();
}
