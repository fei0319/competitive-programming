#include <bits/stdc++.h>

using ll = long long int;

void solve(void) {
    int n;
    std::cin >> n;

    std::vector<int> b;
    int max_value = 0;
    for (int i = 0; i < n; ++i) {
        int t;
        std::cin >> t;

        if (t & 1)
            b.push_back(t);
        max_value = std::max(max_value, t);
    }

    bool flag = false;
    std::sort(b.begin(), b.end());
    for (int i = 1; i < b.size(); ++i) {
        if (i % 2 == 1 && b[i] > i) {
            flag = true;
            break;
        }
    }

    if (flag || max_value > b.size()) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}