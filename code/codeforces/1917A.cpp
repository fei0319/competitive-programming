#include <bits/stdc++.h>

using ll = long long int;

void solve(void) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    int signedness = 1, p = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        if (a[i] == 0) signedness = 0;
        if (a[i] < 0) signedness *= -1;
        if (a[i] > 0) p = i;
    }

    switch (signedness) {
    case 1:
        std::cout << "1\n" << p + 1 << " 0\n";
        break;
    case -1:
        std::cout << "0\n";
        break;
    case 0:
        std::cout << "0\n";
        break;
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