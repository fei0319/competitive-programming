#include <iostream>

int main() {
    int n, k;
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        std::cout << i << ' ' << i << '\n';
        std::cout << i << ' ' << i % n + 1 << '\n';
    }

    k -= n * 2;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (k == 0) {
                return 0;
            }
            if (j == i || j == i % n + 1) {
                continue;
            }
            std::cout << i << ' ' << j << '\n';
            k -= 1;
        }
    }
}