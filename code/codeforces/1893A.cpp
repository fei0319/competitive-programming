#include <bits/stdc++.h>

using ll = long long int;

void solve(void) {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    int start = 0;
    std::vector<uint8_t> vist(n);
    while (k--) {
        int back = (start + n - 1) % n;
        int x = a[back];
        if (x > n) {
            std::cout << "No\n";
            return;
        }
        if (vist[back]) {
            std::cout << "Yes\n";
            return;
        }
        vist[back] = true;
        start = (back - x + 1 + n) % n;
    }
    std::cout << "Yes\n";
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