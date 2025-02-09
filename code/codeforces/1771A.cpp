#include <bits/stdc++.h>

int main() {
    int T;
    std::cin >> T;
    while (T--) {
        int n;
        std::cin >> n;
        std::vector<int> a(n);
        for (int &i : a) std::cin >> i;
        int min = a[0], min_c = 1, max = a[0], max_c = 1;
        for (int i = 1; i < n; ++i) {
            if (a[i] < min) min = a[i], min_c = 1;
            else if (a[i] == min)
                ++min_c;
            if (a[i] > max) max = a[i], max_c = 1;
            else if (a[i] == max)
                ++max_c;
        }
        if (min == max) {
            std::cout << (long long)n * (n - 1) << std::endl;
        } else
            std::cout << (long long)min_c * max_c * 2 << std::endl;
    }
}