#include <bits/stdc++.h>

int main() {
    const int m = 6;
    const int a[m] = {1, 5, 10, 50, 100, 500};

    std::vector<int> c(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> c[i];
    }

    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        for (int j = m - 1; j >= 0; --j) {
            int t = std::min(c[j], x / a[j]);
            c[j] -= t;
            x -= t * a[j];
        }
        if (x) {
            std::cout << "No\n";
            return 0;
        }
    }

    std::cout << "Yes\n";
    return 0;
}