#include <bits/stdc++.h>

using ll = long long int;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::set<int> s;
    std::unordered_map<int, int> fa;

    std::function<int(int)> getf = [&](int x) -> int {
        return fa[x] == x ? x : fa[x] = getf(fa[x]);
    };
    auto add = [&](int x) {
        s.insert(x);
        fa[x] = x;
        if (s.find(x + 1) != s.end()) {
            fa[x + 1] = x;
        }
        if (s.find(x - 1) != s.end()) {
            fa[x] = x - 1;
        }
    };

    for (int i = 0; i < n; ++i) {
        int x = a[i] + i + 1;
        if (s.find(x) == s.end()) {
            add(x);
        } else {
            int rt = getf(x) - 1;
            if (x - i <= rt) {
                add(rt);
            }
        }
    }

    a.clear();
    for (auto i : s) {
        a.push_back(i);
    }
    for (int i = a.size() - 1; i >= 0; --i) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';
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