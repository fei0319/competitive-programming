#include <bits/stdc++.h>

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n, k;
        std::cin >> n >> k;

        std::cout << (n - 1) * k + 1 << '\n';
    }
}