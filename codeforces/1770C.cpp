#include <bits/stdc++.h>

using ll = long long int;

constexpr int maxn = 1e5 + 19;

ll a[maxn];
bool vist[maxn];
std::vector<int> prime;

void solve(void) {
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    std::sort(a + 1, a + 1 + n);
    for (int i = 1; i < n; ++i)
        if (a[i] == a[i + 1]) {
            std::cout << "NO\n";
            return;
        }

    std::vector<std::vector<int>> exc(prime.size());

    for (int i = 1; i < n; ++i)
        for (int j = i + 1; j <= n; ++j) {
            for (int k = 0; k < prime.size(); ++k)
                if ((a[i] - a[j]) % prime[k] == 0)
                    exc[k].push_back(a[i] % prime[k]);
        }

    for (int i = 0; i < prime.size(); ++i) {
        std::sort(exc[i].begin(), exc[i].end());
        exc[i].resize(std::unique(exc[i].begin(), exc[i].end()) -
                      exc[i].begin());
        if (exc[i].size() == prime[i]) {
            std::cout << "NO\n";
            return;
        }
    }
    std::cout << "YES\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    constexpr int N = 200;
    for (int i = 2; i <= N; ++i) {
        if (!vist[i]) {
            prime.push_back(i);
            for (int j = i + i; j <= N; j += i)
                vist[j] = true;
        }
    }

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}