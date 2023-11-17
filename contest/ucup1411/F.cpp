#include <iostream>
#include <vector>
#include <array>

std::vector<uint8_t> sieve(int n) {
    std::vector<uint8_t> is_prime(n + 1, true);
    std::vector<int> primes;

    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
        for (int j : primes) {
            if (j * i > n) {
                break;
            }
            is_prime[j * i] = false;
            if (i % j == 0) {
                break;
            }
        }
    }
    return is_prime;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int &i : a) {
        std::cin >> i;
    }

    auto is_prime = sieve(2e5);
    // dp[i][0 even / 1 odd / 2 one][modified or not]

    const int INF = 1e9;
    std::vector<std::array<std::array<int, 2>, 3>> dp(n);
    for (auto &i : dp) {
        for (auto &j : i) {
            for (auto &k : j) {
                k = INF;
            }
        }
    }

    auto type = [](int x) {
        if (x == 1) {
            return 2;
        }
        return x & 1;
    };
    auto update = [](int &x, int y) {
        if (y < x) {
            x = y;
        }
    };
    std::vector<std::vector<int>> G {std::vector<int> {1, 2}, std::vector<int> {0}, std::vector<int> {0, 2}};

    dp[0][type(a[0])][0] = 0;
    for (int i = 0; i < 3; ++i) {
        dp[0][i][1] = 1;
    }

    auto get = [](auto x) {
        int res = INF;
//        for (int i = 0; i < 3; ++i ) {
//            for (int j = 0; j < 2; ++j) {
//                std::cout << "dp_" << i << "_" << j << "=" << x[i][j] << '\n';
//            }
//        }
        for (auto &i : x) {
            for (auto j : i) {
                res = std::min(res, j);
            }
        }
        return res;
    };

    for (int i = 1; i < n; ++i) {
        // unmodified
        int t = type(a[i]);
//        std::cout << a[i] << ":\n";
        for (int b : G[t]) {
            if (b != 2 || is_prime[a[i] + 1])
            update(dp[i][t][0], dp[i - 1][b][1]);
        }
        if (is_prime[a[i] + a[i - 1]]) {
            update(dp[i][t][0], dp[i - 1][type(a[i - 1])][0]);
//            std::cout << a[i] + a[i - 1] << " is prime\n";
        }

        // modified
        for (int t = 0; t < 3; ++t) {
            for (int b : G[t]) {
                update(dp[i][t][1], dp[i - 1][b][1] + 1);
            }
        }
        for (int t = 0; t < 2; ++t) {
            for (int b : G[t]) {
                update(dp[i][t][1], dp[i - 1][b][0] + 1);
            }
        }
        if (is_prime[a[i - 1] + 1])
            update(dp[i][2][1], dp[i - 1][type(a[i - 1])][0] + 1);

//        std::cout << get(dp[i]) << '\n';
    }

    std::cout << get(dp[n - 1]) << '\n';
}
