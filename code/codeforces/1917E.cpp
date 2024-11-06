#include <bits/stdc++.h>

using ll = long long int;

template <typename T1, typename T2>
struct std::hash<std::pair<T1, T2>> {
    std::size_t operator()(const std::pair<T1, T2> &b) const {
        return std::hash<T1>()(b.first) ^ std::hash<T2>()(b.second);
    }
};

void solve(void) {
    int n, k;
    std::cin >> n >> k;

    if (n == 2 && k == 2) {
        std::cout << "Yes\n"
                     "1 0\n"
                     "0 1\n";
        return;
    }

    if (k % 2 != 0 || k == n * n - 2 || k == 2) {
        std::cout << "No\n";
        return;
    }

    if (n == 4 && k % 4 == 2) {
        if (k == 6) {
            std::cout << "Yes\n"
                         "1 1 0 0\n"
                         "1 0 1 0\n"
                         "0 1 1 0\n"
                         "0 0 0 0\n";
            return;
        }
    }

    std::vector<std::vector<int>> a(n, std::vector<int>(n));

    auto accept = [&](int x, int y) {
        a[x][y] ^= 1;
        a[x + 1][y] ^= 1;
        a[x][y + 1] ^= 1;
        a[x + 1][y + 1] ^= 1;
    };

    int x = 0, y = 0;
    int rest = 0;

    if (k / 4 == 1) {
        accept(0, 0);
        x = y = 1;
    } else if (k / 4 == 2 && k % 4 == 0) {
        accept(0, 0);
        accept(0, 2);
    } else if (k / 4 >= 2) {
        accept(2, 0);
        accept(0, 2);
        accept(2, 2);
        x = y = 1;
        rest = (k + 2) / 4 - 3;
    }

    for (int i = 0; i < n && rest; i += 2) {
        for (int j = 0; j < n && rest; j += 2) {
            if (i == 0 && j == 0 && k % 4 == 2) continue;
            if (!a[i][j]) {
                accept(i, j);
                rest -= 1;
            }
        }
    }

    if (k % 4 == 2) {
        a[x][y] ^= 1;
        a[x + 1][y] ^= 1;
        a[x][y + 1] ^= 1;
        a[x + 1][y + 1] ^= 1;
    }

    std::cout << "Yes\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << a[i][j] << ' ';
        }
        std::cout << '\n';
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